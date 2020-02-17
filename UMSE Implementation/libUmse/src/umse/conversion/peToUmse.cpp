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
#include <include/umse/conversion/peToUmse.h>
#include <kaitaistream.h>
#include <microsoft_pe.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <include/memstream.h>
#include "include/constants.h"
#include <openssl/evp.h>
#include <include/config.h>
#define AES_KEY_LENGHT 32

#ifdef __cplusplus
extern "C" {
    #include <include/umse/umseUtils.h>
}
#endif

/** \brief This functions gets the confidentiality level configured for a given PE section name
 *
 * \param section const char*
 * \return uint32_t
 *
 */
uint32_t getPESectionConfidentiality(const char* section) {
    if(strcmp(section, ".text")   == 0) return PE_TEXT_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".rdata")  == 0) return PE_RDATA_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".data")   == 0) return PE_DATA_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".pdata")  == 0) return PE_PDATA_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".didat")  == 0) return PE_DIDAT_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".rsrc")   == 0) return PE_RSRC_SECTION_CONFIDENTIALITY;
    if(strcmp(section, ".reloc")  == 0) return PE_RSRC_SECTION_CONFIDENTIALITY;
    if(strcmp(section, "overlay") == 0) return PE_OVERLAY_CONFIDENTIALITY;
    return PE_DEFAULT_SECTION_CONFIDENTIALITY;
}

/** \brief This function calculates all metadata entries for a given PE Section
 *
 * \param chunk unsigned char*
 * \param chunkSize int
 * \param numberOfMetadataEntries int*
 * \param entryMetadataLength int*
 * \return unsigned char*
 *
 */
unsigned char* getSectionMetadata(unsigned char* chunk, int chunkSize, int* numberOfMetadataEntries, int* entryMetadataLength){
    // TODO: IMPLEMENT!!
    *numberOfMetadataEntries = 0;
    *entryMetadataLength = 0;
    return NULL;
}

/** \brief This function converts a Portable Executable to UMSE (Universal Malware Sample Encryption) format
 *
 * \param peLength int
 * \param pe unsigned char*
 * \param umseLength unsigned int*
 * \param umse unsigned char**
 * \return void
 *
 */
void peToUmse(int peLength, unsigned char* pe, unsigned int* umseLength, unsigned char** umse){

    // Convert buffer to PE Kaitai Structure
    memstream in(pe, peLength);
    kaitai::kstream ks(&in);
    microsoft_pe_t data(&ks);

    // Iterate over PE sections
    std::vector<microsoft_pe_t::section_t*>* sections = data.sections();
    std::vector<microsoft_pe_t::section_t*>::iterator ptr;
    uint32_t pointer_to_raw_data = 0;
    uint32_t size_of_raw_data = 0;
    uint32_t confidentiality = PE_DEFAULT_SECTION_CONFIDENTIALITY;
    int numFileEntries = 0;
    int decryptionTableLength = 0;
    unsigned char* decryptionTable = createDecryptionTable(
                                                    PE_NUM_CONFIDENTIALITY_LEVELS,
                                                    &decryptionTableLength
    );

    int entriesLength = 0;
    unsigned char* entries = 0;
    int numberOfMetadataEntries = 0;
    int entryMetadataLength = 0;

    for (ptr = (*sections).begin(); ptr < (*sections).end(); ptr++) {
        if(strcmp((*ptr)->name().c_str(), "overlay") != 0){
            confidentiality = getPESectionConfidentiality((*ptr)->name().c_str());
        }

        // Pointer to raw data
        pointer_to_raw_data = (*ptr)->pointer_to_raw_data();

        // Size of raw data
        size_of_raw_data = (*ptr)->size_of_raw_data();

        if(entriesLength == 0){
            // Create an entry for the chunk containing bytes from the start of the file until the first section offset
            unsigned char* entryMetadata = getSectionMetadata(
                                              pe,
                                              pointer_to_raw_data * sizeof(char),
                                              &numberOfMetadataEntries,
                                              &entryMetadataLength
            );
            int entryLength = 0;
            unsigned char* entry = createEntry(
                                   PE_PE_HEADER_CONFIDENTIALITY,
                                   decryptionTable,
                                   pointer_to_raw_data,
                                   pe,
                                   numberOfMetadataEntries,
                                   entryMetadataLength * sizeof(char),
                                   entryMetadata,
                                   &entryLength
            );
            free(entryMetadata);

            entriesLength = entryLength;
            entries = entry; numFileEntries++;
        }


        //Encrypt section
        unsigned char* entryMetadata = getSectionMetadata(
                                                      (pe + pointer_to_raw_data),
                                                      size_of_raw_data * sizeof(char),
                                                      &numberOfMetadataEntries,
                                                      &entryMetadataLength
        );

        int entryLength = 0;
        unsigned char* entry = createEntry(
                                   confidentiality,
                                   decryptionTable,
                                   size_of_raw_data * sizeof(char),
                                   (pe + pointer_to_raw_data),
                                   numberOfMetadataEntries,
                                   entryMetadataLength * sizeof(char),
                                   entryMetadata,
                                   &entryLength
        );
        free(entryMetadata);

        int newLength =  entriesLength + entryLength;
        entries = (unsigned char*) realloc(entries, newLength * sizeof(char));
        if(entries) {
            memcpy(entries+entriesLength, entry, entryLength * sizeof(char));
            entriesLength = newLength; numFileEntries++;
        }
    }

    // Retrieve the overlay
    pointer_to_raw_data += size_of_raw_data; // pointer_to_raw_data stores the offset where overlay starts
    size_of_raw_data = peLength - pointer_to_raw_data;
    if(size_of_raw_data<=0){
            size_of_raw_data = 0; // size_of_raw_data stores the overlay size
    }else{
        unsigned char* entryMetadata = getSectionMetadata(
                                              (pe + pointer_to_raw_data),
                                              size_of_raw_data * sizeof(char),
                                              &numberOfMetadataEntries,
                                              &entryMetadataLength
        );

        int entryLength = 0;
        unsigned char* entry = createEntry(
                                   getPESectionConfidentiality("overlay"),
                                   decryptionTable,
                                   size_of_raw_data * sizeof(char),
                                   (pe + pointer_to_raw_data),
                                   numberOfMetadataEntries,
                                   entryMetadataLength * sizeof(char),
                                   entryMetadata,
                                   &entryLength
        );
        free(entryMetadata);

        int newLength =  entriesLength + entryLength;
        entries = (unsigned char*) realloc(entries, newLength * sizeof(char));
        if(entries) {
            memcpy(entries+entriesLength, entry, entryLength * sizeof(char));
            entriesLength = newLength; numFileEntries++;
        }
    }

    // Create UMSE File
    unsigned char* umseFile = 0;
    int umseFileLength = 0;
    int umseHeaderLength = 0;

    // Copy UMSE Header to UMSE File
    unsigned char* umseHeader = createUmseHeader(PE_NUM_CONFIDENTIALITY_LEVELS, numFileEntries, (char*) PE_MWR_SAMPLE_OWNER, &umseHeaderLength);
    if(!umseHeader) return;

    umseFile       = umseHeader;
    umseFileLength = umseHeaderLength;

    // Encrypt AES keys with RSA and copy resulting UMSE Decryption Table to UMSE File
    int encryptedDecryptionTableLength = 0;
    unsigned char* encryptedDecryptionTable = NULL;
    encryptDecryptionTableWithRSAPubKey(
                                    decryptionTableLength * sizeof(char),
                                    decryptionTable,
                                    (char*) PUBLIC_KEY,
                                    &encryptedDecryptionTableLength,
                                    &encryptedDecryptionTable
    );
    int oldUmseFileLength = umseFileLength;
    umseFileLength += encryptedDecryptionTableLength;
    umseFile = (unsigned char*) realloc(umseFile, umseFileLength * sizeof(char));
    memcpy(umseFile+oldUmseFileLength, encryptedDecryptionTable, encryptedDecryptionTableLength * sizeof(char));
    free(encryptedDecryptionTable);

    // Copy UMSE File Entries to UMSE File
    oldUmseFileLength = umseFileLength;
    umseFileLength += entriesLength;
    umseFile = (unsigned char*) realloc(umseFile, umseFileLength * sizeof(char));
    memcpy(umseFile+oldUmseFileLength, entries, entriesLength * sizeof(char));
    free(entries);


    // Copy File Properties to UMSE File
    unsigned char* sha256Checksum = 0;
    simpleSHA256(pe, peLength, &sha256Checksum);
    numberOfMetadataEntries = 0;
    int fileMetadataLength = 0;
    unsigned char* fileMetadata = getFileMetadata(
                                          pe,
                                          peLength * sizeof(char),
                                          &numberOfMetadataEntries,
                                          &fileMetadataLength
    );

    int filePropertiesLength = 0;
    unsigned char* fileProperties = createFileProperties(
                                                    PE_DEFAULT_SECTION_CONFIDENTIALITY,
                                                    sha256Checksum,
                                                    numberOfMetadataEntries,
                                                    fileMetadataLength * sizeof(char),
                                                    fileMetadata,
                                                    &filePropertiesLength
    );
    free(fileMetadata);
    oldUmseFileLength = umseFileLength;
    umseFileLength += filePropertiesLength;
    umseFile = (unsigned char*) realloc(umseFile, umseFileLength * sizeof(char));
    memcpy(umseFile+oldUmseFileLength, fileProperties, filePropertiesLength * sizeof(char));
    free(fileProperties);

    // Create UMSE Authentication Block
    unsigned char* authenticationBlock;
    int authenticationBlockLength;
    createUmseAuthenticationBlock(
                            decryptionTableLength * sizeof(char),
                            decryptionTable,
                            umseFileLength * sizeof(char),
                            umseFile,
                            &authenticationBlockLength,
                            &authenticationBlock
    );
    free(decryptionTable);
    oldUmseFileLength = umseFileLength;
    umseFileLength += authenticationBlockLength;
    umseFile = (unsigned char*) realloc(umseFile, umseFileLength * sizeof(char));
    memcpy(umseFile+oldUmseFileLength, authenticationBlock, authenticationBlockLength * sizeof(char));
    free(authenticationBlock);


    // Return UMSE file
    *umseLength = umseFileLength;
    *umse       = umseFile;
}
