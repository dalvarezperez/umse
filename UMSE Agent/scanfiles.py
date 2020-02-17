#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: Recursive File Scanner
*  Description: This module scans storage devices, some registry keys...
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

import threading, subprocess, os
from PyQt5 import QtWidgets
import hashlib
import datetime
import os, string
import json
import psutil
import winreg
import ctypes
import intelligenceclient

MAX_FILE_SIZE = 100000000
LIST_OF_EXTENSIONS = ['exe', 'doc', 'docx', 'docm', 'hta', 'html', 'htm', 'js', 'jar',
'vbs', 'vb', 'pdf', 'sfx', '.bat', 'dll', 'tmp', 'py', 'msi', 'msp', 'com', 'gadget',
'cmd', 'vbe', 'jse', 'ps1', 'ps1xml', 'ps2xml', 'psc1', 'psc2', 'lnk', 'inf', 'scf', 'reg']
 
def get_process_list_sorted_by_memory_usage():
    '''
    This function gets the list of running process sorted by Memory Usage
    '''
    listOfProcObjects = []
    # Iterate over the list
    for proc in psutil.process_iter():
       try:
           # Fetch process details as dict
           pinfo = proc.as_dict(attrs=['cmdline', 'connections', 'cpu_affinity', 'cpu_percent', 'cpu_times', 'create_time', 'cwd', 'environ', 'exe', 'io_counters', 'ionice', 'memory_full_info', 'memory_info', 'memory_maps', 'memory_percent', 'name', 'nice', 'num_ctx_switches', 'num_handles', 'num_threads', 'open_files', 'pid', 'ppid', 'status', 'threads', 'username'])
           pinfo['vms'] = proc.memory_info().vms / (1024 * 1024)
           # Append dict to list
           listOfProcObjects.append(pinfo)
       except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
           pass
 
    # Sort list of dict by key vms i.e. memory usage
    listOfProcObjects = sorted(listOfProcObjects, key=lambda procObj: procObj['vms'], reverse=True)
    return listOfProcObjects

def get_registry_key(key_path):
    '''
    This function gets registry key values from a given entry
    '''
    key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, key_path)
    i=0
    registry_keys=[]
    while True:
        try:
            registry_keys.append(winreg.EnumValue(key, i))
            i+=1
        except:
            break
    return registry_keys

def peToUmse(file_path, file_hash):
    '''
    This function converts a Microsoft Windows Portable Executable file
    into an Universal Malware Sample Encryption file
    '''
    file_name = file_path.split("\\")[-1:][0]
    lib_umse_dll = ctypes.cdll.LoadLibrary("libUmse.dll")
    umse_size = ctypes.c_int()
    umse = ctypes.POINTER(ctypes.c_ubyte)()
    pe_bytes = ""
    pe_bytes_length = 0
    with open(file_path, "rb") as f:
        pe_bytes = f.read()
        pe_bytes_length = len(pe_bytes)
    lib_umse_dll.ChunkToUmse(ctypes.c_int(pe_bytes_length), ctypes.c_char_p(pe_bytes), ctypes.byref(umse_size), ctypes.byref(umse))
    umse_filename = ".\\samples\\{0}.umse".format(file_hash)
    with open(umse_filename, "wb") as umse_file:
        umse_file.write(bytearray(umse[:umse_size.value]))
    intelligenceclient.upload_file(umse_filename, file_name)

class ScanFiles(QtWidgets.QSystemTrayIcon):
    def __init__(self, parent):
        super(ScanFiles, self).__init__()
        if(len(threading.enumerate())>2):
            parent.showMessage("UMSE Agent", "UMSE Agent is already collecting samples.")
        else:
            parent.showMessage("UMSE Agent", "Malware sample collection started")
            self.active_scan()
            parent.showMessage("UMSE Agent", "Malware sample collection finished")

    def active_scan(self):
            scan_date=datetime.datetime.now()
            f = open("report.txt", "at")
            f.write("---------------- Scanning report " + str(scan_date) +" ------------------\n")

            f.write("\n\n[*] Files:\n")
            storage_devices = ['%s:' % d for d in string.ascii_uppercase if os.path.exists('%s:' % d)]
            for device_letter in storage_devices:
                if(os.path.exists(device_letter)):
                    for root,dirs,files in os.walk(device_letter):
                        for file in files:
                            try:
                                current_file = os.path.join(root+"\\", file)
                                # Only samples with a known extension are interesting
                                analyze_this_file=False
                                for extension in LIST_OF_EXTENSIONS:
                                    if(current_file.endswith('.' + extension)):
                                        analyze_this_file = True
                                        break
                                if(not analyze_this_file):
                                    continue
                                # If the file is too big it can not be sent
                                if(os.path.getsize(current_file) > MAX_FILE_SIZE):
                                    continue
                                # Submit unknown samples
                                file_hash = self.hash_file(current_file)
                                if(not self.is_known_sample(file_hash)):
                                    f.write("{0} -> {1}\n".format(file_hash, current_file))
                                    peToUmse(current_file, file_hash)
                            except:
                                pass

            f.write(" [*] Processes:\n")
            processes = get_process_list_sorted_by_memory_usage()
            for process in processes:
                f.write("PID: {0} - Name: {1} - Parent ID: {2} - CommandLine: {3}\n".format(process['pid'], process['name'], process['ppid'], process['cmdline']))

            f.write("\n\n[*] Registry Keys:\n")
            registry_keys=get_registry_key("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")
            for registry_key in registry_keys:
                f.write(str(registry_key)+"\n")
            f.write("------------- End scanning report " + str(scan_date) +" ------------------\n\n\n")
            f.close()

    def is_known_sample(self, sample_hash):
        '''
        Checks if an UMSE file do exist or not into the Intelligence Database
        '''
        try:
            return json.loads(intelligenceclient.get_file_info(sample_hash)).get("status")!='error'
        except:
            return False

    def hash_file(self, filepath):
        '''
        This function calcs the sha256 hash of a given file
        '''
        sha256 = hashlib.sha256()
        try:
            with open(filepath, 'rb') as f:
                sha256.update(f.read())
        except:
            return
        return sha256.hexdigest()