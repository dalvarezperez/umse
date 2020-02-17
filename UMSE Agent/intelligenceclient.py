#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: Intelligence Console client
*  Description: This module implements Intelligence Console communication
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

import requests
ENDPOINT = 'http://127.0.0.1:8080'

def upload_file(file_path, original_filename):
    '''
    This function submits an UMSE file to the Intelligence Server
    '''
    url = ENDPOINT+'/upload'
    params= {"original_filename" : original_filename}
    files = {'ufile': open(file_path, 'rb')}
    r = requests.post(url, params=params, files=files)
    return r.text

def get_file_info(file_hash):
    '''
    This function retrieves UMSE file information from the Intelligence Server given the sample hash
    '''
    url = ENDPOINT+'/intelligence'
    query = {'sample_hash': file_hash}
    r = requests.post(url, query)
    return r.text

if __name__== "__main__":
    upload_file("samples\\b3d7aab8ad319dcf7050fe8ce67d69c8c59adc0d90c19a144c2d5c1f66c1babf.umse", "nombre.exe")
    get_file_info("ae8a8a81b218f2c80224fdd318f8e6a9e9bd8cea3f3630952916fe1454fead0b")