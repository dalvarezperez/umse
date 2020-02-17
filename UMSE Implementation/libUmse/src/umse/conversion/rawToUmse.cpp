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
#include <include/umse/conversion/rawToUmse.h>
#include "include/constants.h"
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <include/memstream.h>
#include <openssl/evp.h>
#include <include/config.h>
#define AES_KEY_LENGHT 32

#ifdef __cplusplus
extern "C" {
    #include <include/umse/umseUtils.h>
}
#endif

/** \brief This function calculates all metadata for a given raw data
 *
 * \param chunk unsigned char*
 * \param chunkSize int
 * \param numberOfMetadataEntries int*
 * \param entryMetadataLength int*
 * \return unsigned char*
 *
 */
unsigned char* getRawMetadata(unsigned char* chunk, int chunkSize, int* numberOfMetadataEntries, int* entryMetadataLength){
    // TODO: IMPLEMENT!!
    *numberOfMetadataEntries = 0;
    *entryMetadataLength = 0;
    return NULL;
}

/** \brief This function converts given RAW Data to UMSE (Universal Malware Sample Encryption) format
 *
 * \param rawLength int
 * \param raw unsigned char*
 * \param umseLength unsigned int*
 * \param umse unsigned char**
 * \return void
 *
 */
void rawToUmse(int rawLength, unsigned char* raw, unsigned int* umseLength, unsigned char** umse){
    // Create decryption table
    int decryptionTableLength = 0;
    unsigned char* decryptionTable = createDecryptionTable(
                                                    RAW_NUM_CONFIDENTIALITY_LEVELS,
                                                    &decryptionTableLength
    );

    // Create an entry containing the entire raw data
    int numFileEntries = 1;
    int numberOfMetadataEntries = 0;
    int entryMetadataLength = 0;
    unsigned char* entryMetadata = getRawMetadata(
                                      raw,
                                      rawLength * sizeof(char),
                                      &numberOfMetadataEntries,
                                      &entryMetadataLength
    );

    int entriesLength = 0;
    unsigned char* entries = createEntry(
                           RAW_DEFAULT_CONFIDENTIALITY,
                           decryptionTable,
                           rawLength * sizeof(char),
                           raw,
                           numberOfMetadataEntries,
                           entryMetadataLength * sizeof(char),
                           entryMetadata,
                           &entriesLength
    );
    free(entryMetadata);




    // Create UMSE File
    unsigned char* umseFile = 0;
    int umseFileLength = 0;
    int umseHeaderLength = 0;

    // Copy UMSE Header to UMSE File
    unsigned char* umseHeader = createUmseHeader(RAW_NUM_CONFIDENTIALITY_LEVELS, numFileEntries, (char*) RAW_MWR_SAMPLE_OWNER, &umseHeaderLength);
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
    simpleSHA256(raw, rawLength, &sha256Checksum);
    numberOfMetadataEntries = 0;
    int fileMetadataLength = 0;
    unsigned char* fileMetadata = getFileMetadata(
                                          raw,
                                          rawLength * sizeof(char),
                                          &numberOfMetadataEntries,
                                          &fileMetadataLength
    );

    int filePropertiesLength = 0;
    unsigned char* fileProperties = createFileProperties(
                                                    RAW_DEFAULT_CONFIDENTIALITY,
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
