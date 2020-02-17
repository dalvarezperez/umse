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

/**
 * @file umseUtils.h
 *
 * @brief All necessary functions to create an UMSE file from the scratch
 *
 * @author David Alvarez (https://www.linkedin.com/in/davidalvarezperez/)
 * Contact: dalvarezperez87@gmail.com
 *
 */

#include <stdbool.h>

/** \brief This function creates an UMSE header
 *
 * \param numRecordsDecTable int
 * \param numFileEntries int
 * \param authorNameValue char*
 * \param headerLength int*
 * \return unsigned char*
 *
 */
unsigned char* createUmseHeader(
                        int numRecordsDecTable,
                        int numFileEntries,
                        char* authorNameValue,
                        int* headerLength
);

/** \brief This function creates a plaintext decryption table, so, remember to encrypt it with encryptDecryptionTableWithRSAPubKey
 *
 * \param numberOfConfidentilityLevels int
 * \param decryptionTableLength int*
 * \return unsigned char*
 *
 */
unsigned char* createDecryptionTable(
                                int numberOfConfidentilityLevels,
                                int* decryptionTableLength
);

/** \brief
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
int createUmseAuthenticationBlock(
                            int decryptionTableLength,
                            unsigned char* decryptionTable,
                            int umseLength,
                            unsigned char* umse,
                            int* authenticationBlockLength,
                            unsigned char** authenticationBlock
);

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
int encryptDecryptionTableWithRSAPubKey(
                                    int decryptionTableLength,
                                    unsigned char* decryptionTable,
                                    char* rsaPublicKey,
                                    int* encryptedDecryptionTableLength,
                                    unsigned char** encryptedDecryptionTable
);


/** \brief This function performs AES encryption of a given plaintext message
 *
 * \param aesKeyLength int
 * \param aes_key unsigned char*
 * \param ivLength int
 * \param iv unsigned char*
 * \param plainTextMessageLength int
 * \param plainTextMessage unsigned char*
 * \param encryptedMessageLength int*
 * \param encryptedMessage unsigned char**
 * \return int
 *
 */
int encryptAES(
            int aesKeyLength,
            unsigned char* aes_key,
            int ivLength,
            unsigned char* iv,
            int textPlainMessageLength,
            unsigned char* textPlainMessage,
            int* encryptedMessageLength,
            unsigned char** encryptedMessage
);

/** \brief This function performs AES decryption of a given ciphertext
 *
 * \param aesKeyLength int
 * \param aes_key unsigned char*
 * \param ivLength int
 * \param iv unsigned char*
 * \param encryptedMessageLength int
 * \param encryptedMessage unsigned char*
 * \param plainTextMessageLength int*
 * \param plainTextMessage unsigned char**
 * \return int
 *
 */
int decryptAES(
            unsigned int aesKeyLength,
            unsigned char* aes_key,
            unsigned int ivLength,
            unsigned char* iv,
            unsigned int encryptedMessageLength,
            unsigned char* encryptedMessage,
            unsigned int* plainTextMessageLength,
            unsigned char** plainTextMessage
);


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
unsigned char* createEntry(char confidentilityLevel,
                           unsigned char* decryptionTable,
                           int textPlainMessageLength,
                           unsigned char* textPlainMessage,
                           int numberOfMetadataEntries,
                           int entryMetadataLength,
                           unsigned char* entryMetadata,
                           int* entryLength
);


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
                    unsigned int aesWrappedLength,
                    unsigned char* aesWrapped,
                    char* rsaPrivateKey,
                    unsigned int encryptedEntryLength,
                    unsigned char* encryptedEntry,
                    unsigned int* entryLength,
                    unsigned char** entry
);


/** \brief This function creates an UMSE entry metadata representing an entry disclosable property, useful to decide about to decrypt it or not.
 *
 * \param metadataId char*
 * \param entryLength int
 * \param entryValue char*
 * \return unsigned char*
 *
 */
unsigned char* createEntryMetadata(
                            char* metadataId,
                            int entryLength,
                            char* entryValue
);


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
unsigned char* createFileProperties(
                                char levelOfConfidentility,
                                unsigned char* hashValue,
                                int numberOfMetadataEntries,
                                int metadataLength,
                                unsigned char* metadata,
                                int* filePropertiesLength
);

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
bool simpleSHA256(
            void* input,
            unsigned long length,
            unsigned char** md
);


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
unsigned char* getFileMetadata(
                        unsigned char* chunk,
                        int chunkSize,
                        int* numberOfMetadataEntries,
                        int* fileMetadataLength
);
