/**
 *
 * Copyright (c) 2019-2020. The UMSE Authors. All Rights Reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "include/constants.h"
#include "include/config.h"
#include "include/main.h"
#include <kaitaistream.h>
#include <microsoft_pe.h>
#include <umse.h>
#include <fstream>
#include <streambuf>
#include <include/umse/conversion/peToUmse.h>
#include <include/umse/conversion/rawToUmse.h>
#include <string.h>
#include <include/memstream.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/hmac.h>
#define AES_KEY_LENGHT 32
#define AES_IV_LENGHT 16


#ifdef __cplusplus
extern "C" {
    #include <include/umse/umseUtils.h>
}
#endif


/** \brief This function converts a chunk to Universal Malware Sample Encryption format.
 *
 * \param chunkLength unsigned int
 * \param chunk unsigned char*
 * \param umseSize unsigned int*
 * \param umse unsigned char**
 * \return void DLL_EXPORT
 *
 */
void DLL_EXPORT ChunkToUmse(unsigned int chunkLength, unsigned char* chunk, unsigned int* umseSize, unsigned char** umse)
{
    // Checks if chunk matches Portable Executable format
    try {
        if(chunkLength>2 && (memcmp(chunk, "MZ", 2)==0)){
            memstream in(chunk, chunkLength);
            kaitai::kstream ks(&in);
            microsoft_pe_t::mz_placeholder_t mz_placeholder(&ks);
            peToUmse(chunkLength, chunk, umseSize, umse);
            return;
        }
    }catch (const std::exception& e) {}

    // If chunk has an unknown format then it is handled as RAW data
    try {
        rawToUmse(chunkLength, chunk, umseSize, umse);
        return;
    }catch (const std::exception& e) {}
}



/** \brief This function checks UMSE integrity
 *
 * \param umseLength unsigned int
 * \param umse unsigned char*
 * \param rsaPrivateKey char*
 * \return bool DLL_EXPORT true if Integrity header is valid, in other case it returns false
 *
 */
bool DLL_EXPORT CheckUmseIntegrity(unsigned int umseLength, unsigned char* umse, char* rsaPrivateKey)
{
    try {
        if(umseLength>4 && (memcmp(umse, "UMSE", 4*sizeof(char))==0)){
            // Parse UMSE chunk
            memstream in(umse, umseLength);
            kaitai::kstream ks(&in);
            umse_t umse_file(&ks);

            // Read given RSA Private key
            const char* pem_key_buffer = rsaPrivateKey;
            BIO* bio = BIO_new_mem_buf(pem_key_buffer, -1);
            EVP_PKEY* privKey = NULL;
            PEM_read_bio_PrivateKey(bio, &privKey, NULL, NULL);
            BIO_free(bio);
            RSA* rsa = EVP_PKEY_get1_RSA(privKey);
            int aesEncryptedWithRSALengthBytes = RSA_size( rsa );

            // Reconstruct unencrypted decryption table
            unsigned int unencryptedDecryptionTableLength = umse_file.umse_header()->num_records_dec_table() * (1 + AES_IV_LENGHT + AES_KEY_LENGHT);
            unsigned char* unencryptedDecryptionTable = (unsigned char*) malloc(unencryptedDecryptionTableLength * sizeof(unsigned char*));
            if(unencryptedDecryptionTable == NULL){
                return false;
            }
            unsigned char* ptrUnencryptedDecryptionTable = unencryptedDecryptionTable;
            std::vector<umse_t::decryption_table_t*>* decryption_table_entries = umse_file.decryption_table();
            std::vector<umse_t::decryption_table_t*>::iterator ptrDecryptionTableEntries = (*decryption_table_entries).begin();
            for (ptrDecryptionTableEntries = (*decryption_table_entries).begin(); ptrDecryptionTableEntries < (*decryption_table_entries).end(); ptrDecryptionTableEntries++) {
                unsigned char level_of_confidentiality = (*ptrDecryptionTableEntries)->level_of_confidentiality();
                memcpy(ptrUnencryptedDecryptionTable, &level_of_confidentiality, 1*sizeof(char)); ptrUnencryptedDecryptionTable += 1;
                unsigned char* aes_wrapped = ((*ptrDecryptionTableEntries)->aes_wrapped()->size()? &(*ptrDecryptionTableEntries)->aes_wrapped()->front():nullptr);
                unsigned int aes_wrapped_length = (*ptrDecryptionTableEntries)->aes_wrapped()->size();
                RSA_private_decrypt(aes_wrapped_length,
                                     aes_wrapped,
                                     ptrUnencryptedDecryptionTable,
                                     rsa,
                                     RSA_PKCS1_OAEP_PADDING);
                ptrUnencryptedDecryptionTable += (AES_IV_LENGHT + AES_KEY_LENGHT);
            }

            // Calculate hash of unencrypted decryption table
            unsigned char* sha256 = 0;
            unsigned int sha256Length = 32;
            simpleSHA256(unencryptedDecryptionTable, unencryptedDecryptionTableLength, &sha256);

            // Calculate HMAC of UMSE file
            unsigned int umseLengthWithoutAuthAndRsaKeyBlock = 0x1A; // 0x1A is the length of the UMSE Header
            umseLengthWithoutAuthAndRsaKeyBlock += (umse_file.umse_header()->num_records_dec_table() * (256 + 1)); // Decryption table length
            std::vector<umse_t::entry_t*>* umse_entries = umse_file.entry();
            for ( std::vector<umse_t::entry_t*>::iterator it = (*umse_entries).begin(); it != (*umse_entries).end(); ++it) {
                umseLengthWithoutAuthAndRsaKeyBlock += (4+1+4); // length of size, levelOfConfidentiality and numMetadata
                umseLengthWithoutAuthAndRsaKeyBlock += (*it)->encrypted_message()->size(); // Entry length
                if((*it)->num_metadata()>0){
                    std::vector<umse_t::entry_metadata_t*>* ptrEntryMetadata = (*it)->entry_metadata();
                    for ( std::vector<umse_t::entry_metadata_t*>::iterator itMetadata = (*ptrEntryMetadata).begin(); itMetadata != (*ptrEntryMetadata).end(); ++itMetadata) {
                        umseLengthWithoutAuthAndRsaKeyBlock += (8 + 4); // length of 'tag' and 'length' fields
                        umseLengthWithoutAuthAndRsaKeyBlock += (*itMetadata)->length(); // Metadata entry length
                    }
                }
            }
            std::vector<umse_t::file_metadata_t*>* ptrFileMetadata =  umse_file.file_properties()->file_metadata();
            umseLengthWithoutAuthAndRsaKeyBlock += 1+32+4; // length levelOfConfidentiality, length hashValue, length numMetadata
            if(umse_file.file_properties()->num_metadata()>0){
                for ( std::vector<umse_t::file_metadata_t*>::iterator it = (*ptrFileMetadata).begin(); it != (*ptrFileMetadata).end(); ++it) {
                    umseLengthWithoutAuthAndRsaKeyBlock += 8 + 4; // length of tag, length of length
                    umseLengthWithoutAuthAndRsaKeyBlock += (*it)->length();
                }
            }
            unsigned int hmacDigestLength = 0;
            unsigned char* hmacDigest = HMAC(EVP_sha256(), sha256, sha256Length, umse, umseLengthWithoutAuthAndRsaKeyBlock, NULL, &hmacDigestLength);

            // Get HMAC stored in UMSE Authentication Block
            if(hmacDigestLength != umse_file.authentication_header()->hmac()->size()){
                    return false;
            }
            unsigned char umseFileDigest[hmacDigestLength];
            memcpy(umseFileDigest, umse_file.authentication_header()->hmac()->data(), hmacDigestLength);

            // Compare both HMAC values
            if(memcmp(hmacDigest, umseFileDigest, hmacDigestLength) == 0){
                return true;
            };
        }
    }catch (const std::exception& e) {}

    return false;
}


/** \brief If UMSE integrity check is successful and the accessLevel is less than or equal to the confidentiality level, this function decrypts an entry of a given UMSE file chunk and its RSA Private key.
 *
 * \param umseLength unsigned int
 * \param umse unsigned char*
 * \param entryToDecrypt unsigned int
 * \param accessLevel unsigned int
 * \param rsaPrivateKey char*
 * \param decryptedEntryLength unsigned int*
 * \param decryptedEntry unsigned char**
 * \return int DLL_EXPORT
 *
 */
int DLL_EXPORT DecryptUmse(unsigned int umseLength, unsigned char* umse, unsigned int entryToDecrypt, unsigned int accessLevel, char* rsaPrivateKey, unsigned int* decryptedEntryLength, unsigned char** decryptedEntry)
{
    *decryptedEntryLength = 0;
    *decryptedEntry = 0;
    int retVal = 0;

    // Check integrity before decryption
    if (!CheckUmseIntegrity(umseLength, umse, rsaPrivateKey)) return -2;

    // UMSE Decryption routine
    try {
        // Parse UMSE chunk
        memstream in(umse, umseLength);
        kaitai::kstream ks(&in);
        umse_t umse_file(&ks);

        // Get encrypted entry
        std::vector<umse_t::entry_t*>* umse_entries = umse_file.entry();
        std::vector<umse_t::entry_t*>::iterator ptrUmseEntries;
        unsigned int i = 0;
        for (ptrUmseEntries = (*umse_entries).begin(); ptrUmseEntries < (*umse_entries).end(); ptrUmseEntries++) {
            if( i<entryToDecrypt ) {
                i++;
            }else{
                break;
            }
        }
        if(i!=entryToDecrypt) return -1;

        // Compare the access level with the entry confidentiality level
        unsigned int level_of_confidentiality = (*ptrUmseEntries)->level_of_confidentiality();
        if(accessLevel>level_of_confidentiality) return -3;
        std::vector<uint8_t>* encrypted_entry = (*ptrUmseEntries)->encrypted_message();
        int encryptedEntryLength = encrypted_entry->size();
        unsigned char* encryptedEntry = (encrypted_entry->size()? &encrypted_entry->front():nullptr);

        // Get Encrypted AES Key
        std::vector<umse_t::decryption_table_t*>* decryption_table_entries = umse_file.decryption_table();
        std::vector<umse_t::decryption_table_t*>::iterator ptrDecryptionTableEntries = (*decryption_table_entries).begin();
        i = 0;
        while( level_of_confidentiality != (*ptrDecryptionTableEntries)->level_of_confidentiality() &&
               ptrDecryptionTableEntries < (*decryption_table_entries).end()) {
            i++;
            ptrDecryptionTableEntries++;
        }
        if(level_of_confidentiality != (*ptrDecryptionTableEntries)->level_of_confidentiality()) return;
        std::vector<uint8_t>* aes_wrapped = (*ptrDecryptionTableEntries)->aes_wrapped();
        int ivAndAesWrappedLength = aes_wrapped->size();
        unsigned char* ivAndAesWrapped = (ivAndAesWrappedLength? &aes_wrapped->front():nullptr);

        // Call to decrypt entry
        decryptEntryWithRSAPrivKey(
                            ivAndAesWrappedLength,
                            ivAndAesWrapped,
                            rsaPrivateKey,
                            encryptedEntryLength,
                            encryptedEntry,
                            decryptedEntryLength,
                            decryptedEntry
        );

    }catch (const std::exception& e) {}
    return retVal;
}


#ifdef _DEBUG
/** \brief This function reads a file
 *
 * \param path char*
 * \param length unsigned long*
 * \return unsigned char*
 *
 */
unsigned char* ReadFile(char *path, unsigned long* length)
{
	FILE *file;
	unsigned char *buffer;

	//Open file
	file = fopen(path, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", path);
		return 0;
	}

	//Get file length
	fseek(file, 0, SEEK_END);
	*length=ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer=(unsigned char *)malloc(*length+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(file);
		return 0;
	}

	//Read file contents into buffer
	fread(buffer, *length, 1, file);
	fclose(file);

	return buffer;
}
#endif // DEBUG

/** \brief DllMain function
 *
 * \param hinstDLL HINSTANCE
 * \param fdwReason DWORD
 * \param lpvReserved LPVOID
 * \return extern "C" DLL_EXPORT BOOL APIENTRY
 *
 */
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            #ifdef _DEBUG
            char currentDirectory[MAX_PATH];
            GetCurrentDirectory( MAX_PATH, currentDirectory );
            // TESTING PE TO UMSE
                unsigned long fileContentLength = 0;
                char pesample[MAX_PATH];
                strcpy(pesample,currentDirectory);
                strcat(pesample, "\\libUmse\\test\\samples\\test.exe");
                unsigned char* fileContent = ReadFile((char*) pesample, &fileContentLength);
                if(fileContent){
                    unsigned int umseSize = 0;
                    unsigned char* umse = 0;
                    ChunkToUmse(fileContentLength, fileContent, &umseSize, &umse);
                    if(umse){
                        char petoumse[MAX_PATH];
                        strcpy(petoumse,currentDirectory);
                        strcat(petoumse, "\\libUmse\\bin\\Debug\\petoumse.umse");
                        FILE * file = fopen(petoumse, "wb");
                        if (!file)
                        {
                            fprintf(stderr, "Unable to open file %s", "petoumse.umse");
                            break;
                        }
                        fwrite (umse , sizeof(char), umseSize, file);
                        fclose (file);

                        // Cleanup
                        free(umse);
                    }
                    // Cleanup
                    free(fileContent);
                }
            // TESTING RAW TO UMSE
                fileContentLength = 0;
                char csample[MAX_PATH];
                strcpy(csample,currentDirectory);
                strcat(csample, "\\libUmse\\test\\samples\\test.c");
                fileContent = ReadFile((char*) csample, &fileContentLength);
                if(fileContent){
                    unsigned int umseSize = 0;
                    unsigned char* umse = 0;
                    ChunkToUmse(fileContentLength, fileContent, &umseSize, &umse);
                    if(umse){
                        char rawtoumse[MAX_PATH];
                        strcpy(rawtoumse,currentDirectory);
                        strcat(rawtoumse, "\\libUmse\\bin\\Debug\\rawtoumse.umse");
                        FILE * file = fopen(rawtoumse, "wb");
                        if (!file)
                        {
                            fprintf(stderr, "Unable to open file %s", "rawtoumse.umse");
                            break;
                        }
                        fwrite (umse , sizeof(char), umseSize, file);
                        fclose (file);

                        // Cleanup
                        free(umse);
                    }
                    // Cleanup
                    free(fileContent);
                }
            // TESTING DECRYPTION
                fileContentLength = 0;
                char petoumse[MAX_PATH];
                strcpy(petoumse,currentDirectory);
                strcat(petoumse, "\\libUmse\\bin\\Debug\\petoumse.umse");
                fileContent = ReadFile((char*) petoumse, &fileContentLength);
                long unsigned int rsaPrivateKeyLength = 0;
                char rsaprivatekey[MAX_PATH];
                strcpy(rsaprivatekey,currentDirectory);
                strcat(rsaprivatekey, "\\libUmse\\test\\keys\\private_key.pem");
                char* rsaPrivateKey = (char*) ReadFile((char*) rsaprivatekey, &rsaPrivateKeyLength);
                unsigned int decryptedEntryLength;
                unsigned char* decryptedEntry;
                unsigned int entryToDecrypt = 0;
                unsigned int accessLevel = 0;
                DecryptUmse(fileContentLength, fileContent, entryToDecrypt, accessLevel, rsaPrivateKey, &decryptedEntryLength, &decryptedEntry);
                if(decryptedEntry){
                    char decryptedEntryPath[MAX_PATH];
                    strcpy(decryptedEntryPath,currentDirectory);
                    strcat(decryptedEntryPath, "\\libUmse\\bin\\Debug\\decryptedEntryPE.bin");
                    FILE * file = fopen(decryptedEntryPath, "wb");
                    if (!file)
                    {
                        fprintf(stderr, "Unable to open file %s", "decryptedEntryPE.bin");
                        break;
                    }
                    fwrite (decryptedEntry , sizeof(char), decryptedEntryLength, file);
                    fclose (file);

                    // Cleanup
                    free(decryptedEntry);
                }
                fileContentLength = 0;
                char rawtoumse[MAX_PATH];
                strcpy(rawtoumse,currentDirectory);
                strcat(rawtoumse, "\\libUmse\\bin\\Debug\\rawtoumse.umse");
                fileContent = ReadFile((char*) rawtoumse, &fileContentLength);
                rsaPrivateKeyLength = 0;
                decryptedEntryLength = 0;
                decryptedEntry = 0;
                entryToDecrypt = 0;
                accessLevel = 0;
                DecryptUmse(fileContentLength, fileContent, entryToDecrypt, accessLevel, rsaPrivateKey, &decryptedEntryLength, &decryptedEntry);
                if(decryptedEntry){
                    char decryptedEntryPath[MAX_PATH];
                    strcpy(decryptedEntryPath,currentDirectory);
                    strcat(decryptedEntryPath, "\\libUmse\\bin\\Debug\\decryptedEntryC.bin");
                    FILE * file = fopen(decryptedEntryPath, "wb");
                    if (!file)
                    {
                        fprintf(stderr, "Unable to open file %s", "decryptedEntryC.bin");
                        break;
                    }
                    fwrite (decryptedEntry , sizeof(char), decryptedEntryLength, file);
                    fclose (file);

                    // Cleanup
                    free(decryptedEntry);
                }
                // Cleanup
                free(fileContent);
            #endif // DEBUG
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
