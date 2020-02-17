#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: UMSE Decryption Tools
*  Description: This module allows to decrypt UMSE file entries.
*
*  Copyright (c) 2019-2020. The UMSE Authors. All Rights Reserved.
*  Redistribution and use in source and binary forms, with or without modification,
*  are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, this
*  list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice,
*  this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. Neither the name of the copyright holder nor the names of its contributors
*  may be used to endorse or promote products derived from this software without
*  specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
"""

import Crypto
#import umse
import ctypes
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Cipher import AES


RSA_PEM_FILE_PATH = "rsa_private_key.pem"

def get_rsa_private_key_from_pem_file(pem_file_path):
    '''
    This function reads the rsa private key from the given PEM file
    '''
    with open(pem_file_path, "rt") as rsa_priv_key_file:
        return rsa_priv_key_file.read()

'''
@deprecated(version='0.1', reason="Crypto library not longer used for RSA encryption and decryption")
def rsa_decryption(ciphertext, pem_file_path):
    ciphertext = bytearray(ciphertext)
    rsa_priv_key = get_rsa_private_key_from_pem_file(pem_file_path)
    dsize = SHA.digest_size
    dcipher = PKCS1_OAEP.new(rsa_priv_key)
    aes_key = dcipher.decrypt(ciphertext)
    return aes_key

@deprecated(version='0.1', reason="Crypto library not longer used for RSA encryption and decryption")
def aes_decryption(aes_key, encrypted_message):
    pad = lambda s: s + (AES.block_size - len(s) % AES.block_size) * chr(AES.block_size - len(s) % AES.block_size)
    unpad = lambda s: s[:-ord(s[len(s) - 1:])]
    aes_iv = b"\0"*AES.block_size
    aes_cipher = AES.new(aes_key, AES.MODE_CBC, aes_iv)
    data = unpad(aes_cipher.decrypt(encrypted_message))
    return data

@deprecated(version='0.1', reason="Crypto library not longer used for RSA encryption and decryption")
def get_aes_key_from_entry_to_decrypt(entry_to_decrypt, umse_sample):
    if(entry_to_decrypt >= umse_sample.umse_header.num_file_entries):
        return None
    entry_to_decrypt_confidentiality = umse_sample.entry[entry_to_decrypt].level_of_confidentiality
    for i in range(umse_sample.umse_header.num_records_dec_table):
        if(umse_sample.decryption_table[i].level_of_confidentiality == entry_to_decrypt_confidentiality):
            aes_key = rsa_decryption(umse_sample.decryption_table[i].aes_wrapped, RSA_PEM_FILE_PATH)
            return aes_key
    return None
 
@deprecated
def get_encrypted_message_from_entry(entry_to_decrypt, umse_sample):
    if(entry_to_decrypt >= umse_sample.umse_header.num_file_entries):
        return None
    entry_to_decrypt_confidentiality = umse_sample.entry[entry_to_decrypt].level_of_confidentiality
    for i in range(umse_sample.umse_header.num_records_dec_table):
        if(umse_sample.decryption_table[i].level_of_confidentiality == entry_to_decrypt_confidentiality):
            encrypted_message = bytearray(umse_sample.entry[entry_to_decrypt].encrypted_message)
            return encrypted_message
    return None
'''

class GeneralError(Exception):
    pass

class InvalidAuthenticationHeader(Exception):
    pass

class InsufficientCredentials(Exception):
    pass

def decrypt_entry(entry_to_decrypt, umse_sample, access_level):
    '''
    This function decrypts an UMSE file entry
    '''
    rsa_private_key = get_rsa_private_key_from_pem_file(RSA_PEM_FILE_PATH).encode("ascii")
    lib_umse_dll = ctypes.cdll.LoadLibrary("libUmse.dll")
    decryptedEntryLength = ctypes.c_int()
    decryptedEntry = ctypes.POINTER(ctypes.c_ubyte)()
    umse_bytes = umse_sample
    umse_bytes_length = len(umse_bytes)
    lib_umse_dll.DecryptUmse.restype = ctypes.c_int
    ret_val = lib_umse_dll.DecryptUmse(ctypes.c_int(umse_bytes_length), ctypes.c_char_p(umse_bytes), ctypes.c_int(entry_to_decrypt), ctypes.c_int(access_level), ctypes.c_char_p(rsa_private_key), ctypes.byref(decryptedEntryLength), ctypes.byref(decryptedEntry))
    if(ret_val != 0):
        if(ret_val == -1):
            raise GeneralError('General error')
        if(ret_val == -2):
            raise InvalidAuthenticationHeader('Invalid UMSE authentication header.')
        elif(ret_val == -3):
            raise InsufficientCredentials('Insufficient credentials.')
    return bytearray(decryptedEntry[:decryptedEntryLength.value])

'''
def decrypt_entry(entry_to_decrypt, umse_sample):
    aes_key = get_aes_key_from_entry_to_decrypt(entry_to_decrypt, umse_sample)
    encrypted_message = get_encrypted_message_from_entry(entry_to_decrypt, umse_sample)
    decrypted_entry = aes_decryption(aes_key, encrypted_message)
    return decrypted_entry
'''