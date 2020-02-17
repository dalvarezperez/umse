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
 * @file main.h
 *
 * @brief Dll main and exported functions implementation
 *
 * @author David Alvarez (https://www.linkedin.com/in/davidalvarezperez/)
 * Contact: dalvarezperez87@gmail.com
 *
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
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
void DLL_EXPORT ChunkToUmse(unsigned int chunkLength, unsigned char* chunk, unsigned int* umseSize, unsigned char** umse);


/** \brief If UMSE integrity check is successful, this function decrypts an entry of a given Universal Malware Sample Encryption file chunk and its RSA Private key.
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
int DLL_EXPORT DecryptUmse(unsigned int umseLength, unsigned char* umse, unsigned int entryToDecrypt, unsigned int accessLevel, char* rsaPrivateKey, unsigned int* decryptedEntryLength, unsigned char** decryptedEntry);



/** \brief This function checks UMSE integrity
 *
 * \param umseLength unsigned int
 * \param umse unsigned char*
 * \param rsaPrivateKey char*
 * \return bool DLL_EXPORT true if Integrity header is valid, in other case it returns false
 *
 */
bool DLL_EXPORT CheckUmseIntegrity(unsigned int umseLength, unsigned char* umse, char* rsaPrivateKey);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
