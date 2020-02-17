#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: UMSE Shell
*  Description: This module allows interaction with "UMSE Intelligence Server".
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

from cmd import Cmd
import requests
import re
import os
import json
import base64
import subprocess
import hashlib
import getpass

ENDPOINT = 'http://127.0.0.1:8080'
DECRYPTED_SAMPLES_DIRECTORY = 'decrypted_samples'
DOWNLOADED_SAMPLES_DIRECTORY = 'downloaded_samples'

_010EDITOR = "C:\\Program Files\\010 Editor\\010Editor.exe"
RADARE2 = '{0}\\AppData\\Local\\Programs\\radare2\\radare2.exe'.format(os.getenv('USERPROFILE'))
USERNAME = None
PASSWORD = None
PROMPT = "UMSE> "
BANNER = '''\n ____ ____ ____ ____ 
||U |||M |||S |||E ||
||__|||__|||__|||__||
|/__\\|/__\\|/__\\|/__\\|\n'''

class MyCmd(Cmd):

    prompt = PROMPT

    def do_decrypt(self, args):
        '''
        It Decrypts an UMSE entry.
        Syntax: decrypt [sample_hash] [umse_entry_id]
            sample_hash = sample's hash
            umse_entry_id = Identifier of the UMSE entry to decrypt
        '''
        message = 'Command error. Syntax: decrypt [sample_hash] [umse_entry_id]'
        if(USERNAME is None):
            print("You are not logged in. Use the 'login' command first.")
            return
        try:
            url = ENDPOINT+'/decrypt_sample'
            arg_list = args.split()
            if(len(arg_list)!=2):
                return
            file_hash = arg_list[0]
            entry = arg_list[1]
            query = {'sample_hash': file_hash, 'entry': entry, 'username': USERNAME, 'password': PASSWORD}
            message = 'Entry {0} from sample {1} was sucessfully decrypted.'.format(entry, file_hash)
            r = requests.post(url, query)
            if r.status_code == 401:
                print("You are not allowed to decrypt this entry. This operation attempt was registered.")
                return
            if r.status_code == 500:
                print("A general error was raised by the server.")
                return
            d = r.headers['content-disposition']
            fname = re.findall("filename=(.+)", d)[0]
            decrypted_chunk_filepath = '{0}/{1}'.format(DECRYPTED_SAMPLES_DIRECTORY, fname)
            with open(decrypted_chunk_filepath, "wb") as f:
                f.write(base64.b64decode(bytearray(r.text.encode("utf-8"))))
            subprocess.call([RADARE2,decrypted_chunk_filepath])
        except requests.exceptions.RequestException as e:
            print("      Error: Unable to connect to: {0}".format(ENDPOINT))
        except Exception as e:
            print(str(e))

    def do_login(self, args):
        '''
        Intelligence Server login command.
        Once logged in, It allows you to decrypt UMSE sample entries depending on the user privilege.
        '''
        global USERNAME
        global PASSWORD
        global prompt
        url = ENDPOINT+'/check_credentials'
        username_tmp = input('Username: ')
        password_tmp = hashlib.sha256(getpass.getpass(prompt='Password: ').encode("utf-8")).hexdigest()
        query = {'username': username_tmp, 'password': password_tmp}
        try:
            r = requests.post(url, query)
            if(r.text=='ok'):
                USERNAME = username_tmp
                PASSWORD = password_tmp
                self.prompt = USERNAME+'@'+PROMPT
        except requests.exceptions.RequestException as e:
            print("      Error: Unable to connect to: {0}".format(ENDPOINT))
        except Exception as e:
            print(str(e))

    def do_list(self, args):
        '''
        Shows the complete list of malware UMSE samples from Intelligence Console
        '''
        try:
            url = ENDPOINT+'/get_all_samples'
            r = requests.get(url)
            samples = json.loads(r.text)
            for sample in samples:
                print("{0} - {1} - {2}".format(samples[sample].get('hash_sha256'), samples[sample].get('original_filename'), samples[sample].get('sample_size')))
        except requests.exceptions.RequestException as e:
            print("      Error: Unable to connect to: {0}".format(ENDPOINT))
        except Exception as e:
            print(str(e))

    def do_download(self, args):
        '''
        Use this command to download UMSE samples.
            Syntax: download [sample_hash]
            sample_hash = Sample hash 
        '''
        if(len(args.strip())!=64):
            print("      Error: SHA256 argument expected.")
            return
        try:
            url = ENDPOINT+'/intelligence'
            query = {'sample_hash': args}
            r = requests.post(url, query)
            sample = json.loads(r.text)
            file_content = base64.b64decode(sample.get('file_content'))
            fname = sample.get('hash_sha256')+".umse"
            umse_filepath = '{0}/{1}'.format(DOWNLOADED_SAMPLES_DIRECTORY, fname)
            with open(umse_filepath, "wb") as f:
                f.write(file_content)
            print("[!] SAMPLE DOWNLOADED TO: {0}".format(umse_filepath))
            subprocess.call([_010EDITOR, umse_filepath])
        except requests.exceptions.RequestException as e:
            print("      Error: Unable to connect to: {0}".format(ENDPOINT))
        except Exception as e:
            print(str(e))

    def do_clear(self, args):
        '''
        Clear screen
        '''
        os.system("cls")

    def do_exit(self, args):
        '''
        Exit the shell
        '''
        global USERNAME
        global PASSWORD
        if(USERNAME is not None):
            self.prompt = PROMPT
            USERNAME = None
            PASSWORD = None
        else:
            raise SystemExit()


if __name__ == "__main__":
    os.system("cls")
    if not os.path.exists(DECRYPTED_SAMPLES_DIRECTORY):
        os.makedirs(DECRYPTED_SAMPLES_DIRECTORY)
    if not os.path.exists(DOWNLOADED_SAMPLES_DIRECTORY):
        os.makedirs(DOWNLOADED_SAMPLES_DIRECTORY)
    print(BANNER)
    app = MyCmd()
    app.cmdloop('Wellcome to UMSE shell.')