#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: UMSE Intelligence Server
*  Description: This module launch the "UMSE Intelligence Server".
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

from kaitaistruct import KaitaiStream
#import umse
import os
import cherrypy
import base64
import json
import sqlitequeries
import umsedecryptiontools
from io import BytesIO
from datetime import datetime

def check_auth():
    '''
    Takes username and password parameters from POST request, perfomns authentication and returns user data
    '''
    needs_auth = cherrypy.request.config.get('auth.require', False)
    username = None
    password = None
    try:
        username = cherrypy.request.params['username']
        password = cherrypy.request.params['password']
        cherrypy.request.params.pop('password', None)
    except:
        pass
    auth_result = json.loads(sqlitequeries.check_auth(username, password))
    if(needs_auth and auth_result.get('status') != 'ok'):
        raise cherrypy.HTTPError(401)
    else:
    	return True

def needsauth():
    '''
    A decorator that sets auth.require config variable.
    '''
    def decorate(f):
        if not hasattr(f, '_cp_config'):
            f._cp_config = dict()
        if 'auth.require' not in f._cp_config:
            f._cp_config['auth.require'] = []
        f._cp_config['auth.require'] = True
        return f
    return decorate

class App:
    _cp_config = {'tools.auth.on': True,}
    @cherrypy.expose
    def upload(self, ufile, original_filename):
        '''
        This function allows to upload an UMSE file to database
        '''
        #original_filename = ufile.filename
        file_content = b''
        sample_size = 0
        while True:
            data = ufile.file.read(8192)
            if not data:
                break
            file_content = b''.join([file_content, data])
            sample_size += len(data)
        file_hash = ufile.filename.split('.')[0]
        return sqlitequeries.upload_sample(file_hash, original_filename, sample_size, file_content)

    @cherrypy.expose
    def intelligence(self, sample_hash):
        '''
        This function retrieves information of an UMSE sample given its sample hash
        '''
        return sqlitequeries.get_sample_by_hash(sample_hash)

    @cherrypy.expose
    def index(self):
        '''
        This function shows the "index.html" file.
        Index file consists in a paginated table of samples and a search inputbox.
        '''
        result = ""
        with open("tpl\\samples.tpl") as samples_tpl:
            return samples_tpl.read().replace("**SAMPLES_JSON_HERE**", sqlitequeries.get_all_samples())

    @cherrypy.expose
    def get_all_samples(self):
        '''
        This function retrieves information of all UMSE samples available in database
        '''
        return sqlitequeries.get_all_samples()

    @cherrypy.expose
    def download_sample(self, id):
        '''
        This function allows to download an UMSE file sample given its sample identifier
        '''
        samples = json.loads(sqlitequeries.get_samples_by_id_range(str(int(id)-1), str(int(id)+1)))
        for sample in samples:
            cherrypy.response.headers['Content-Type']        = 'application/octet-stream'
            cherrypy.response.headers['Content-Disposition'] = 'attachment; filename={0}.umse'.format(samples[sample].get('hash_sha256'))
            return base64.b64decode(samples[sample].get('file_content'))

    @cherrypy.expose
    @needsauth()
    def decrypt_sample(self, sample_hash, entry, username):
        '''
        This function allows to decrypt an UMSE entry from a given sample (identified by its sample hash)
        '''
        user_data_json = json.loads(sqlitequeries.get_user_data_from_username(username))
        user_id = user_data_json['id']
        access_level = user_data_json['access_level']
        sqlitequeries.log_user_activity(user_id, "{0} User '{1}'' requested to decrypt entry '{2}'' of sample '{3}'".format(str(datetime.now()), username, entry, sample_hash))
        sample = json.loads(sqlitequeries.get_sample_by_hash(sample_hash))
        file_content = base64.b64decode(sample.get('file_content'))
        original_filename = sample.get('original_filename')
        '''stream = KaitaiStream(BytesIO(file_content))
        sample = umse.Umse(stream)'''
        sample = file_content
        decrypted_entry = None
        try:
            decrypted_entry = umsedecryptiontools.decrypt_entry(int(entry), sample, int(access_level))
        except umsedecryptiontools.GeneralError:
            raise cherrypy.HTTPError(500, "General error")
            sqlitequeries.log_user_activity(user_id, "{0} User '{1}'' attempted to decrypt entry '{2}'' of sample '{3}' but a general error was raised.".format(datetime.now(), username, entry, sample_hash))
        except umsedecryptiontools.InvalidAuthenticationHeader:
            sqlitequeries.log_user_activity(user_id, "{0} User '{1}'' attempted to decrypt entry '{2}'' of sample '{3}' but this UMSE file was TAMPERED!!!".format(datetime.now(), username, entry, sample_hash))
            raise cherrypy.HTTPError(500, "Invalid UMSE Authentication Header detected")
        except umsedecryptiontools.InsufficientCredentials:
            sqlitequeries.log_user_activity(user_id, "{0} User '{1}'' attempted to decrypt entry '{2}'' of sample '{3}' but operation was DISALLOWED!!!".format(datetime.now(), username, entry, sample_hash))
            raise cherrypy.HTTPError(401, "User unauthorized to decrypt this UMSE entry")
        cherrypy.response.headers['Content-Type']        = 'application/octet-stream'
        cherrypy.response.headers['Content-Disposition'] = 'attachment; filename={0}.entry{1}'.format(original_filename, entry)
        if(decrypted_entry is not None):
            sqlitequeries.log_user_activity(user_id, "{0} User '{1}'' successfully decrypted entry '{2}'' of sample '{3}'".format(datetime.now(), username, entry, sample_hash))
        return base64.b64encode(decrypted_entry)

    @cherrypy.expose
    @needsauth()
    def check_credentials(self, username):
        '''
        This function allows to check if user credentials are valid or not.
        '''
        return "ok"

if __name__ == '__main__':
    sqlitequeries.create_schema_tables()
    config = {
        '/': {
            'tools.staticdir.root': os.path.abspath( os.getcwd() ),
            'tools.staticfile.root': os.path.abspath( os.getcwd() )
        },
        'global' : {
            'server.socket_host' : '127.0.0.1',
            'server.socket_port' : 8080
        },
        "/favicon.ico": {
            "tools.staticfile.on": True,
            "tools.staticfile.filename": "./favicon.ico"
        },
    }
    cherrypy.tools.auth = cherrypy.Tool('before_handler', check_auth, priority=50)
    cherrypy.quickstart(App(), '/', config)
