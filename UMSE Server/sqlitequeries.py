#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: Intelligence SQLite Database
*  Description: This module allows to query "UMSE Intelligence SQLite Database".
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

import sqlite3
import json
import base64

DATABASE_FILE = 'intelligence.db'

def create_schema_tables():
    '''
    This function creates the SQLite tables: SAMPLES and USERS
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    conn.execute('''CREATE TABLE IF NOT EXISTS SAMPLES
                                                     (id            INTEGER PRIMARY KEY    AUTOINCREMENT UNIQUE NOT NULL,
                                                     hash           CHAR(64)               UNIQUE NOT NULL,
                                                     file_name      CHAR(256)              NOT NULL,
                                                     sample_size    INTEGER                NOT NULL,
                                                     file_content   BLOB);
                ''')
    conn.execute('''CREATE TABLE IF NOT EXISTS CONFIDENTIALITY_LEVELS
                                                     (confidentiality_levels_id    INTEGER PRIMARY KEY    AUTOINCREMENT UNIQUE NOT NULL,
                                                     confidentiality_name          CHAR(64)               UNIQUE NOT NULL,
                                                     confidentiality_description   CHAR(256));
                ''')
    conn.execute('''CREATE TABLE IF NOT EXISTS USERS
                                                     (id                   INTEGER PRIMARY KEY    AUTOINCREMENT UNIQUE NOT NULL,
                                                     username              CHAR(64)               UNIQUE NOT NULL,
                                                     password              CHAR(256)              NOT NULL,
                                                     access_level          INTEGER                NOT NULL,
                                                     FOREIGN KEY(access_level) REFERENCES CONFIDENTIALITY_LEVELS(confidentiality_levels_id));
                ''')
    conn.execute('''CREATE TABLE IF NOT EXISTS USERS_ACTIVITY
                                                     (id                   INTEGER PRIMARY KEY      AUTOINCREMENT UNIQUE NOT NULL,
                                                     users_id              INTEGER                  NOT NULL,
                                                     log_entry             CHAR(256)                NOT NULL,
                                                     FOREIGN KEY(users_id) REFERENCES users(id));
                ''')
    try:
        for i in range(10):
            conn.execute("INSERT INTO CONFIDENTIALITY_LEVELS (confidentiality_name, confidentiality_description) VALUES(?, ?)", [str(i), 'level {0}'.format(i)])
        access_level = 0
        conn.execute("INSERT INTO USERS (username, password, access_level) VALUES('root', 'ce5ca673d13b36118d54a7cf13aeb0ca012383bf771e713421b4d1fd841f539a', ?)", [access_level])
        access_level = 1
        conn.execute("INSERT INTO USERS (username, password, access_level) VALUES('user', '04f8996da763b7a969b1028ee3007569eaf3a635486ddab211d512c85b9df8fb', ?)", [access_level])
    except sqlite3.IntegrityError:
        pass
    conn.commit()
    conn.close()

def log_user_activity(users_id, log_entry):
    try:
        conn = sqlite3.connect(DATABASE_FILE)
        conn.execute("INSERT INTO USERS_ACTIVITY (users_id, log_entry) VALUES(?, ?)", [users_id, log_entry])
    except sqlite3.IntegrityError:
        pass
    conn.commit()
    conn.close()

def upload_sample(file_hash, original_filename, file_content, sample_size):
    '''
    This allows to upload UMSE Samples to the Intelligence console
    '''
    try:
        if(DATABASE_FILE is not None):
            conn = sqlite3.connect(DATABASE_FILE)
            conn.execute("INSERT INTO SAMPLES ( hash, file_name, sample_size, file_content ) VALUES(?, ?, ?, ?)", [file_hash, original_filename, sample_size, file_content])
            conn.commit()
        else:
            # For debugging purposes a samples directory is used when database file is not defined
            samples_directory = os.path.normpath(os.path.join(os.path.dirname(__file__), "samples"))
            os.mkdir(samples_directory)
            upload_file = os.path.normpath(os.path.join(samples_directory, file_hash))
            if (not os.path.exists(upload_file)):
                return
            with open(upload_file, 'wb') as out:
                out.write(file_content)
        result = {
            "status" : "ok",
            "file_hash" : file_hash
        }
    except sqlite3.IntegrityError:
        result = {
            "status" : "error",
            "message" : "Sample hash already exist in database."
        }
    finally:
        conn.close()
    return json.dumps(result, indent=4)

def get_sample_by_hash(sample_hash):
    '''
    This function retrieves a sample given the sample hash
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    cursor = conn.execute("SELECT id, hash, file_name, sample_size, file_content from SAMPLES where hash=?", (sample_hash,))
    result = {
        "status" : "error",
        "message" : "Sample not found in database."
    }
    for row in cursor:
        result = {
            "status" : "ok",
            "id" : row[0],
            "hash_sha256" : row[1],
            "original_filename" : row[2],
            "sample_size" : row[4],
            "file_content" : base64.b64encode(row[3]).decode("utf-8")
        }
    conn.close()
    return json.dumps(result, indent=4)

def check_auth(username, password):
    '''
    This function checks if provided credentials are valid or not.
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    cursor = conn.execute("SELECT id, username, password from USERS where username=? and password=?", (username, password))
    result = {
        "status" : "error",
        "message" : "Invalid credentials."
    }
    for row in cursor:
        result = {
            "status" : "ok",
            "id" : row[0],
            "username" : row[1],
            "password" : row[2]
        }
    conn.close()
    return json.dumps(result, indent=4)

def get_user_data_from_username(username):
    '''
    This function returns the user id of a given username
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    cursor = conn.execute("SELECT id, access_level from USERS where username=?;", (username,))
    result = {
        "status" : "error",
        "message" : "Invalid credentials."
    }
    for row in cursor:
        result = {
            "status" : "ok",
            "id" : row[0],
            "access_level" : row[1]
        }
    conn.close()
    return json.dumps(result, indent=4)

def get_all_samples():
    '''
    This function returns all the database UMSE malware samples.
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    rows = conn.execute("SELECT id, hash, file_name, sample_size, file_content from SAMPLES")
    result = dict()
    for row in rows:
        result['sample{0}'.format(row[0])] = {
                                                "status" : "ok",
                                                "id" : row[0],
                                                "hash_sha256" : row[1],
                                                "original_filename" : row[2],
                                                "sample_size" : row[4]
                                                #"file_content" : base64.b64encode(row[3]).decode("utf-8")
                                            }
    conn.close()
    return json.dumps(result, indent=4)

def get_number_of_samples():
    '''
    This function returns the count of database UMSE malware samples.
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    rows = conn.execute("SELECT COUNT(*) from SAMPLES")
    row = rows.fetchone()
    if row is None:
        row = 0
    count = row[0]
    conn.close()
    result = {
        "status" : "ok",
        "count" : count
    }
    return json.dumps(result, indent=4)

def get_samples_by_id_range(start_index, end_index):
    '''
    This function returns a set of samples (samples matching a range of sample IDs).
    '''
    conn = sqlite3.connect(DATABASE_FILE)
    rows = conn.execute("SELECT id, hash, file_name, sample_size, file_content from SAMPLES where id>? and id<?", (start_index, end_index))
    result = dict()
    i=0
    for row in rows:
        result['sample{0}'.format(row[0])] = {
                                                "status" : "ok",
                                                "id" : row[0],
                                                "hash_sha256" : row[1],
                                                "original_filename" : row[2],
                                                "sample_size" : row[4],
                                                "file_content" : base64.b64encode(row[3]).decode("utf-8")
                                            }
        i+=1
    conn.close()
    return json.dumps(result, indent=4)
