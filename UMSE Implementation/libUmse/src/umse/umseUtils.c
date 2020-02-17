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
#include <include/umse/umseUtils.h>

#define MAGIC "UMSE"
#define MAGIC_LEN 4
#define VERSION " 1.0"
#define VERSION_LEN 4
#define AES_KEY_LENGHT 32
#define AES_IV_LENGHT 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/hmac.h>
#include "include/config.h"

/** \brief This function changes the endianness of an uint32_t value
 *
 * \param val uint32_t
 * \return uint32_t
 *
 */
uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

/** \brief This function creates an UMSE header
 *
 * \param numRecordsDecTable int
 * \param numFileEntries int
 * \param authorNameValue char*
 * \param headerLength int*
 * \return unsigned char*
 *
 */
unsigned char* createUmseHeader(int numRecordsDecTable, int numFileEntries, char* authorNameValue, int* headerLength)
{
    char magic[MAGIC_LEN] = MAGIC;
    char version[VERSION_LEN] = VERSION;
    int authorNameLength = strlen(authorNameValue);

    *headerLength = (
        MAGIC_LEN   +    // magic
        VERSION_LEN +    // version
        4 +              // numRecordsDecTable
        4 +              // numFileEntries
        4 +              // authorNameLength
        authorNameLength // authorNameValue
    );

    unsigned char* umseHeader = (unsigned char*) malloc(*headerLength * sizeof(unsigned char*) );
    if(umseHeader!=NULL){
        unsigned char* ptrUmseHeader = umseHeader;
        memcpy(ptrUmseHeader, magic,                      MAGIC_LEN * sizeof(char));  ptrUmseHeader += (MAGIC_LEN * sizeof(char));
        memcpy(ptrUmseHeader, version,                  VERSION_LEN * sizeof(char));  ptrUmseHeader += (VERSION_LEN * sizeof(char));
        memcpy(ptrUmseHeader, &numRecordsDecTable,                    sizeof(int));   ptrUmseHeader += sizeof(int);
        memcpy(ptrUmseHeader, &numFileEntries,                        sizeof(int));   ptrUmseHeader += sizeof(int);
        memcpy(ptrUmseHeader, &authorNameLength,                      sizeof(int));   ptrUmseHeader += sizeof(int);
        memcpy(ptrUmseHeader, authorNameValue,     authorNameLength * sizeof(char));  ptrUmseHeader += (authorNameLength * sizeof(char));
    }

    return umseHeader;
}

/** \brief This function generates a random AES key with length AES_KEY_LENGHT
 *
 * \return unsigned char*
 *
 */
unsigned char* generateRandomAESKey(){
    unsigned char* aes_key = (unsigned char *) malloc(AES_KEY_LENGHT * sizeof(unsigned char*));
    if(aes_key == NULL){
        return 0;
    }
    memset(aes_key, 0, sizeof(*aes_key));
    if (RAND_bytes(aes_key, AES_KEY_LENGHT * sizeof(aes_key)) == 0)
    {
        free(aes_key);
        aes_key=0;
        return 0;
    }
    return aes_key;
}

/** \brief This function generates a random IV with length AES_IV_LENGHT
 *
 * \return unsigned char*
 *
 */
unsigned char* generateRandomIvForAES(){
    unsigned char* aes_iv = (unsigned char*) malloc(AES_IV_LENGHT * sizeof(unsigned char*));
    if(aes_iv == NULL){
        return 0;
    }
    memset(aes_iv, 0, sizeof(*aes_iv));
    if (RAND_bytes(aes_iv, AES_IV_LENGHT * sizeof(aes_iv)) == 0)
    {
        free(aes_iv);
        aes_iv = 0;
        return 0;
    }
    return aes_iv;
}


/** \brief This function creates a plaintext decryption table, so, remember to encrypt it with encryptDecryptionTableWithRSAPubKey
 *
 * \param numberOfConfidentilityLevels int
 * \param decryptionTableLength int*
 * \return unsigned char*
 *
 */
unsigned char* createDecryptionTable(int numberOfConfidentilityLevels, int* decryptionTableLength)
{
    *decryptionTableLength = (
                        numberOfConfidentilityLevels +
                        ((AES_KEY_LENGHT+AES_IV_LENGHT) * numberOfConfidentilityLevels)
    );
    unsigned char* decryptionTable = (unsigned char *) malloc(*decryptionTableLength * sizeof(char));
    if(decryptionTable == NULL){
        return 0;
    }
    unsigned char* ptrDecryptionTable = decryptionTable;
    for(char i=0; i<numberOfConfidentilityLevels; i++){
        unsigned char* randomAESKey = generateRandomAESKey();
        if(randomAESKey == NULL){
            free(decryptionTable);
            return 0;
        }
        unsigned char* randomIvForAESKey = generateRandomIvForAES();
        if(randomIvForAESKey == NULL){
            free(randomAESKey);
            free(decryptionTable);
            return 0;
        }
        memcpy(ptrDecryptionTable,                &i,                  sizeof(char)); ptrDecryptionTable += sizeof(char);
        memcpy(ptrDecryptionTable, randomIvForAESKey,  AES_IV_LENGHT * sizeof(char)); ptrDecryptionTable += (AES_IV_LENGHT * sizeof(char));
        memcpy(ptrDecryptionTable,      randomAESKey, AES_KEY_LENGHT * sizeof(char)); ptrDecryptionTable += (AES_KEY_LENGHT * sizeof(char));
        free(randomIvForAESKey);
        free(randomAESKey);
    }
    return decryptionTable;
}


/** \brief This function calculates decryption table sha256 hash checksum
 *
 * \param decryptionTableLength int
 * \param decryptionTable unsigned char*
 * \param hashLength int*
 * \param hash unsigned char**
 * \return int
 *
 */
int generateDecryptionTableSHA256(int decryptionTableLength, unsigned char* decryptionTable, int* hashLength, unsigned char** hash)
{
    if(simpleSHA256(decryptionTable, decryptionTableLength, hash)){
        *hashLength = 32;
    }else{
        *hash = 0;
        *hashLength = 0;
        return -1;
    }
    return 0;
};


/** \brief This function creates the UMSE authentication header
 *
 * \param decryptionTableLength int
 * \param decryptionTable unsigned char*
 * \param umseLength int
 * \param umse unsigned char*
 * \param authenticationBlockLength int*
 * \param authenticationBlock unsigned char**
 * \return int
 *
 */
int createUmseAuthenticationBlock(int decryptionTableLength, unsigned char* decryptionTable, int umseLength, unsigned char* umse, int* authenticationBlockLength, unsigned char** authenticationBlock){
    // Generate Decryption Table SHA256
    int sha256Length = 0;
    unsigned char* sha256 = 0;
    generateDecryptionTableSHA256(decryptionTableLength, decryptionTable, &sha256Length, &sha256);
    if(sha256Length == 0 || sha256 == 0){
        return -1;
    }

    // Use Decryption Table SHA256 as HMAC Key for Decryption Table HMAC Digest
    unsigned int decryptionTableHmacDigestLength = 0;
    unsigned char* decryptionTableHmacDigest = HMAC(EVP_sha256(), sha256, sha256Length, umse, umseLength, NULL, &decryptionTableHmacDigestLength);
    #ifdef _DEBUG
    char mdString[decryptionTableHmacDigestLength*2];
    for(int i = 0; i < decryptionTableHmacDigestLength; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)decryptionTableHmacDigest[i]);
    printf("Decryption Table HMAC Digest: %s\n", mdString);
    #endif

    unsigned char* authenticationBlockAux = malloc(4+sha256Length);
    unsigned char* authenticationBlockAuxPtr = authenticationBlockAux;
    if(authenticationBlockAux != NULL){
        memcpy(authenticationBlockAuxPtr, &decryptionTableHmacDigestLength,     sizeof(unsigned int)); authenticationBlockAuxPtr += sizeof(unsigned int);
        memcpy(authenticationBlockAuxPtr, decryptionTableHmacDigest, decryptionTableHmacDigestLength); authenticationBlockAuxPtr += decryptionTableHmacDigestLength;
    }

    *authenticationBlock = authenticationBlockAux;
    *authenticationBlockLength = decryptionTableHmacDigestLength + 4;
    return 0;
}



/** \brief This function encrypts AES keys of a given encryption table with RSA PUBLIC_KEY defined in "config.h" file.
 *
 * \param decryptionTableLength int
 * \param decryptionTable unsigned char*
 * \param rsaPublicKey char*
 * \param encryptedDecryptionTableLength int*
 * \param encryptedDecryptionTable unsigned char**
 * \return int
 *
 */
int encryptDecryptionTableWithRSAPubKey(int decryptionTableLength, unsigned char* decryptionTable, char* rsaPublicKey, int* encryptedDecryptionTableLength, unsigned char** encryptedDecryptionTable)
{
    unsigned char* ptrDecryptionTable = decryptionTable;
    unsigned char* ptrEndDecryptionTable = ptrDecryptionTable + decryptionTableLength;

    // Load RSA Public key
    const char* pem_key_buffer = PUBLIC_KEY;

    BIO* bio = BIO_new_mem_buf(pem_key_buffer, -1);

    EVP_PKEY* pkey = NULL;
    PEM_read_bio_PUBKEY(bio, &pkey, NULL, NULL);
    BIO_free(bio);

    RSA* rsa = EVP_PKEY_get1_RSA(pkey);
    int aesEncryptedWithRSALengthBytes = RSA_size( rsa ) ;

    // Encrypted decryption table pointers
    int encryptedDecryptionTableLengthAux = 0;
    unsigned char* encryptedDecryptionTableAux = NULL;
    unsigned char* ptrEncryptedDecryptionTableAux = NULL;

    while(ptrDecryptionTable != ptrEndDecryptionTable){
        encryptedDecryptionTableLengthAux += (
                                          1 +                          // Length of confidentiality level
                                        aesEncryptedWithRSALengthBytes // Length of an AES key encrypted with RSA public key
        );

        // Allocate space for an encrypted decryption table entry
        if(encryptedDecryptionTableAux == NULL){
            int numEntries = 1;
            while(decryptionTableLength>0){
                decryptionTableLength -= (AES_KEY_LENGHT+AES_IV_LENGHT+1);
                numEntries++;
            }

            encryptedDecryptionTableAux = malloc((encryptedDecryptionTableLengthAux*numEntries) * sizeof(char));
            ptrEncryptedDecryptionTableAux = encryptedDecryptionTableAux;
        }
        if(!encryptedDecryptionTableAux){
            return -1;
        }

        // Fill confidentiality level
        memcpy(ptrEncryptedDecryptionTableAux, ptrDecryptionTable, sizeof(char)); ptrDecryptionTable++; ptrEncryptedDecryptionTableAux++;

        // Encrypt AES using RSA public key and Fill the buffer with it
        int aesKeyEncryptedLength = 0;
        int bytesToEncryptLength = AES_KEY_LENGHT+AES_IV_LENGHT;
        if((aesKeyEncryptedLength = RSA_public_encrypt(
                                                bytesToEncryptLength * sizeof(char),
                                                ptrDecryptionTable,
                                                ptrEncryptedDecryptionTableAux,
                                                rsa,
                                                RSA_PKCS1_OAEP_PADDING)) == -1) {
            return -1;
        }

        ptrDecryptionTable += bytesToEncryptLength;
        ptrEncryptedDecryptionTableAux += aesEncryptedWithRSALengthBytes;
    }

    *encryptedDecryptionTableLength = encryptedDecryptionTableLengthAux;
    *encryptedDecryptionTable = encryptedDecryptionTableAux;

    return 0;
};


/** \brief Decrypts an UMSE entry with the provided RSA private key
 *
 * \param aesWrappedLength int
 * \param aesWrapped unsigned char*
 * \param rsaPrivateKey char*
 * \param encryptedEntryLength int
 * \param encryptedEntry char*
 * \param entryLength int*
 * \param entry unsigned char**
 * \return int
 *
 */
 int decryptEntryWithRSAPrivKey(
                    unsigned int ivAndAesWrappedLength,
                    unsigned char* ivAndAesWrapped,
                    char* rsaPrivateKey,
                    unsigned int encryptedEntryLength,
                    unsigned char* encryptedEntry,
                    unsigned int* entryLength,
                    unsigned char** entry
){
    // Load RSA Private key
    BIO* bio = BIO_new_mem_buf(rsaPrivateKey, -1);
    EVP_PKEY* privkey = NULL;
    PEM_read_bio_PrivateKey(bio, &privkey, NULL, NULL);
    BIO_free(bio);
    RSA* rsa = EVP_PKEY_get0_RSA(privkey);

    // Decrypt IV and AES wrapped Key using provided RSA Private Key
    unsigned char* ivAndAes = malloc(256);
    int decryptedEntryLength = RSA_private_decrypt(
                        ivAndAesWrappedLength,
                        ivAndAesWrapped,
                        ivAndAes,
                        rsa,
                        RSA_PKCS1_OAEP_PADDING);
    if(decryptedEntryLength != AES_KEY_LENGHT + AES_IV_LENGHT){
        return -1;
    }
    unsigned char* iv = ivAndAes;
    unsigned char* aesKey = ivAndAes + AES_IV_LENGHT;

    // Decrypt Entry using AES Key
    decryptAES(
            AES_KEY_LENGHT,
            aesKey,
            AES_IV_LENGHT,
            iv,
            encryptedEntryLength,
            encryptedEntry,
            entryLength,
            entry
    );

    // Remove padding
    *entryLength -= (*entry)[(*entryLength)-1];

    return 0;
};


/** \brief This function performs AES encryption of a given plaintext message
 *
 * \param aesKeyLength int
 * \param aes_key unsigned char*
 * \param aesIvLength int
 * \param aes_iv unsigned char*
 * \param plainTextMessageLength int
 * \param plainTextMessage unsigned char*
 * \param encryptedMessageLength int*
 * \param encryptedMessage unsigned char**
 * \return int
 *
 */
int encryptAES(int aesKeyLength, unsigned char* aes_key, int ivLength, unsigned char* iv, int plainTextMessageLength, unsigned char* plainTextMessage, int* encryptedMessageLength, unsigned char** encryptedMessage){
    EVP_CIPHER_CTX *ctx = NULL;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        return -1;

    EVP_CIPHER_CTX_init(ctx);

    const EVP_CIPHER* cbc = EVP_aes_256_cbc();
    if(1 != EVP_EncryptInit_ex(ctx, cbc, 0, (const unsigned char *) aes_key, iv))
        return -1;

    *encryptedMessage = (unsigned char*) malloc((plainTextMessageLength + AES_BLOCK_SIZE) * sizeof(char));
    if(*encryptedMessage == NULL)
        return -1;

    int count = 0;
    if(1 != EVP_EncryptUpdate(ctx, *encryptedMessage, &count, plainTextMessage, plainTextMessageLength * sizeof(char)))
        return -1;

    *encryptedMessageLength = count;

    if(1 != EVP_EncryptFinal_ex(ctx, *encryptedMessage+count, &count))
        return -1;

    *encryptedMessageLength += count;

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}


/** \brief This function performs AES decryption of a given ciphertext
 *
 * \param aesKeyLength unsigned int
 * \param aes_key unsigned char*
 * \param ivLength int
 * \param iv unsigned char*
 * \param encryptedMessageLength unsigned int
 * \param encryptedMessage unsigned char*
 * \param plainTextMessageLength unsigned int*
 * \param plainTextMessage unsigned char**
 * \return int
 *
 */
int decryptAES(unsigned int aesKeyLength, unsigned char* aes_key, unsigned int ivLength, unsigned char* iv, unsigned int encryptedMessageLength, unsigned char* encryptedMessage, unsigned int* plainTextMessageLength, unsigned char** plainTextMessage){
    EVP_CIPHER_CTX *ctx = NULL;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        return -1;

    EVP_CIPHER_CTX_init(ctx);

    const EVP_CIPHER* cbc = EVP_aes_256_cbc();
    if(1 != EVP_DecryptInit_ex(ctx, cbc, 0, (const unsigned char *) aes_key, iv))
        return -1;

    *plainTextMessage = (unsigned char*) malloc(encryptedMessageLength * sizeof(char));
    if(*plainTextMessage == NULL)
        return -1;

    int count = 0;
    if(1 != EVP_EncryptUpdate(ctx, *plainTextMessage, &count, encryptedMessage, encryptedMessageLength * sizeof(char)))
        return -1;

    *plainTextMessageLength = count;

    if(1 != EVP_DecryptFinal_ex(ctx, *plainTextMessage+count, &count))
        return -1;

    *plainTextMessageLength += count;

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}



/** \brief This function creates an UMSE entry, representing an atomic group of bytes in terms of confidentiality
 *
 * \param confidentilityLevel char
 * \param decryptionTable unsigned char*
 * \param plainTextMessageLength int
 * \param plainTextMessage unsigned char*
 * \param numberOfMetadataEntries int
 * \param entryMetadataLength int
 * \param entryMetadata unsigned char*
 * \param entryLength int*
 * \return unsigned char*
 *
 */
unsigned char* createEntry(char confidentilityLevel, unsigned char* decryptionTable, int plainTextMessageLength, unsigned char* plainTextMessage, int numberOfMetadataEntries, int metadataLength, unsigned char* entryMetadata, int* entryLength){
    unsigned char* ptrDecryptionTableEntry = decryptionTable;
    unsigned char* ptrDecryptionTableEntryKey = NULL;
    unsigned char* ptrDecryptionTableEntryIv = NULL;

    // Search appropiate AES Key and IV for this confidentiality level by parsing decryption table
    ptrDecryptionTableEntry += (AES_KEY_LENGHT + AES_IV_LENGHT + 1)*confidentilityLevel;
    ptrDecryptionTableEntryIv = ptrDecryptionTableEntry + 1;
    ptrDecryptionTableEntryKey = ptrDecryptionTableEntry + AES_IV_LENGHT + 1;
    unsigned char aes_key[AES_KEY_LENGHT];
    memcpy(aes_key, ptrDecryptionTableEntryKey, AES_KEY_LENGHT);
    unsigned char iv[AES_IV_LENGHT];
    memcpy(iv, ptrDecryptionTableEntryIv, AES_IV_LENGHT);

    // Encrypt the plaintext chunk with AES 256
    int encryptedMessageLength = 0;
    unsigned char* encryptedMessage = NULL;
    if(encryptAES(AES_KEY_LENGHT, aes_key, AES_IV_LENGHT, iv, plainTextMessageLength, plainTextMessage, &encryptedMessageLength, &encryptedMessage) !=0)
        return 0;

    // Allocate space for Entry Structure
    *entryLength = (
            4 +                      // entry size
            1 +                      // level of confidentility
            encryptedMessageLength + // Encrypted Message
            4+                       // Number of metadata entries
            metadataLength           // Entry Metadata Length
    );
    unsigned char* entry = (unsigned char *) malloc(*entryLength * sizeof(char));
    if(entry == NULL){
        free(encryptedMessage);
        return 0;
    }

    // Copy data to Entry Structure
    unsigned char* ptrEntry = entry;
    memcpy(ptrEntry, &encryptedMessageLength,                            sizeof(int));  ptrEntry += sizeof(int);
    memcpy(ptrEntry, &confidentilityLevel,                              sizeof(char));  ptrEntry += sizeof(char);
    memcpy(ptrEntry, encryptedMessage,         encryptedMessageLength * sizeof(char));  ptrEntry += encryptedMessageLength * sizeof(char);
    memcpy(ptrEntry, &numberOfMetadataEntries,                           sizeof(int));  ptrEntry += sizeof(int);
    if(numberOfMetadataEntries>0){
        memcpy(ptrEntry, entryMetadata,        metadataLength * sizeof(char));          ptrEntry += metadataLength * sizeof(char);
    }
    return entry;
}


/** \brief This function creates an UMSE entry metadata representing an entry disclosable property, useful to decide about to decrypt it or not.
 *
 * \param metadataId char*
 * \param entryLength int
 * \param entryValue char*
 * \return unsigned char*
 *
 */
unsigned char* createEntryMetadata(char* metadataId, int entryLength, char* entryValue){
    if(metadataId==NULL || strlen(metadataId)!=8) return 0;
    int entryMetadataLength = 8 +          // Metadata ID
                              4 +          // Metadata length
                              entryLength; // Metadata value
    unsigned char* entryMetadata = (unsigned char *) malloc(entryMetadataLength*sizeof(char));
    if(entryMetadata == NULL) return 0;
    unsigned char* ptrEntryMetadata = entryMetadata;
    memcpy(ptrEntryMetadata, metadataId,             8*sizeof(char)); ptrEntryMetadata += 8;
    memcpy(ptrEntryMetadata, &entryLength,           4*sizeof(char)); ptrEntryMetadata += 4;
    memcpy(ptrEntryMetadata, &entryValue,  entryLength*sizeof(char)); ptrEntryMetadata += entryLength;
    return entryMetadata;
}


/** \brief This function performs SHA256 hashing of a given input
 *
 * \param input void*
 * \param length unsigned long
 * \param md unsigned char**
 * \return bool
 *
 */
bool simpleSHA256(void* input, unsigned long length, unsigned char** md)
{
    int sha256LengthBytes = 32;
    SHA256_CTX context;

    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return false;

    *md = malloc(sha256LengthBytes);
    if(!*md) return false;

    if(!SHA256_Final(*md, &context))
        return false;

    return true;
}


/** \brief This function creates the UMSE File Properties section, containing disclosable general information about the encrypted file
 *
 * \param levelOfConfidentility char
 * \param hashName char*
 * \param hashValue unsigned char*
 * \param numberOfMetadataEntries int
 * \param metadataLength int
 * \param metadata unsigned char*
 * \param filePropertiesLength int*
 * \return unsigned char*
 *
 */
unsigned char* createFileProperties(char levelOfConfidentility, unsigned char* hashValue, int numberOfMetadataEntries, int metadataLength, unsigned char* metadata, int* filePropertiesLength)
{
    int hashValueLength = AES_KEY_LENGHT;
    *filePropertiesLength = (
                         1 +               // Level of confidentiality
                         hashValueLength + // Hash value
                         4 +               // Number of metadata entries
                         metadataLength    // Metadata
    );
    unsigned char* fileProperties = (unsigned char *) malloc(*filePropertiesLength * sizeof(char));
    if(fileProperties == NULL) return 0;
    unsigned char* ptrFileProperties = fileProperties;
    memcpy(ptrFileProperties, &levelOfConfidentility,                   sizeof(char));  ptrFileProperties += sizeof(char);
    memcpy(ptrFileProperties, hashValue,               hashValueLength* sizeof(char));  ptrFileProperties += hashValueLength * sizeof(char);
    memcpy(ptrFileProperties, &numberOfMetadataEntries,                  sizeof(int));  ptrFileProperties += sizeof(int);
    if(numberOfMetadataEntries>0){
        memcpy(ptrFileProperties, metadata, metadataLength); ptrFileProperties += metadataLength;
    }

    return fileProperties;
}

/** \brief This function creates an UMSE file metadata representing a disclosable file property, useful to decide if file is malicious or not.
 *
 * \param chunk unsigned char*
 * \param chunkSize int
 * \param numberOfMetadataEntries int*
 * \param fileMetadataLength int*
 * \return unsigned char*
 *
 */
unsigned char* getFileMetadata(unsigned char* chunk, int chunkSize, int* numberOfMetadataEntries, int* fileMetadataLength){
    *numberOfMetadataEntries = 0;
    *fileMetadataLength = 0;
    unsigned char* fileMetadata = NULL;

    // Append PE File identification Metadata
    if(chunkSize>0x41){
        if(memcmp(chunk, "MZ", 2)==0){
            unsigned int peOffset = 0;
            memcpy(&peOffset, &chunk[0x3C], 4*sizeof(char));
            if(chunkSize>peOffset+2){
               if(memcmp(&chunk[peOffset], "PE", 2)==0){
                    *numberOfMetadataEntries +=1;
                    char* jsonMetadata = "FileType\x02\x00\x00\x00PE";
                    int jsonMetadataLength = 14;
                    fileMetadata = malloc(jsonMetadataLength);
                    if(fileMetadata){
                        memcpy(fileMetadata, jsonMetadata, jsonMetadataLength);
                    }
                    *fileMetadataLength = jsonMetadataLength;
               }
            }
        }
    }
    return fileMetadata;
}

