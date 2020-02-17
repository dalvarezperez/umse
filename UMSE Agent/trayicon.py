#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: System Try Icon
*  Description: This module is the System Try Icon.
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

import sys, os, hashlib, threading, webbrowser, subprocess
from PyQt5 import QtCore, QtGui, QtWidgets
import multiprocessing

# Libraries
from aboutform import AboutForm
from scanfiles import ScanFiles


class SystemTrayIcon(QtWidgets.QSystemTrayIcon):

    def __init__(self, icon, parent=None):
        QtWidgets.QSystemTrayIcon.__init__(self, icon, parent)
        menu = QtWidgets.QMenu(parent)

        # RealTime Protection flag
        self.sampleCollectorStatusEnabled = False
        self.collectSamplesStartText="Collect malware samples"
        self.collectSamplesStopText="Stop to collect malware samples"
        self.icon="resources\\start.ico"

        # Adding actions to the interface.
        self.collectorAction = menu.addAction(QtGui.QIcon(self.icon), self.collectSamplesStartText, self.collectSamples)
        menu.addSeparator()
        self.aboutAction = menu.addAction(QtGui.QIcon("resources\\agent.ico"), "About", self.aboutWindow)
        self.internetAction = menu.addAction(QtGui.QIcon("resources\\agent.ico"), "UMSE Agent on Internet", self.viewWebSite)
        self.exitAction = menu.addAction(QtGui.QIcon("resources\\exit.ico"), "Exit", self.exit)
        self.setContextMenu(menu)


    # Logical action definitions
    def collectSamples(self):
        '''
        Starts to collect malware samples from the system
        '''
        current_status = self.sampleCollectorStatusEnabled
        self.updatesampleCollectorStatus()
        if(current_status):
            self.collectSamplesInBackground(False)
        else:
            self.collectSamplesInBackground(True)

    def aboutWindow(self):
        '''
        Shows the about window
        '''
        AboutForm().exec_()

    def updatesampleCollectorStatus(self):
        '''
        Updates the sample collector status indicator
        '''
        if (self.sampleCollectorStatusEnabled):
            self.icon="resources\\start.ico"
            self.collectorAction.setText(self.collectSamplesStartText)
            self.collectorAction.setIcon(QtGui.QIcon(self.icon))
            self.sampleCollectorStatusEnabled=False
        else:
            self.icon="resources\\stop.ico"
            self.collectorAction.setText(self.collectSamplesStopText)
            self.collectorAction.setIcon(QtGui.QIcon(self.icon))
            self.sampleCollectorStatusEnabled=True

    def viewWebSite(self):
        '''
        Opens the UMSE website in browser
        '''
        webbrowser.open("https://github.com/dalvarezperez/umse")

    def exit(self):
        '''
        Exists from the program
        '''
        sys.exit()

    def collectSamplesInBackground(self, start):
        '''
        Collects malware samples in background
        '''
        if(start):
            self.hilo=threading.Thread(target=self.scanMyFiles, args=())
            self.hilo.daemon = True
            self.hilo.start()
        else:
            self.hilo.do_stop = True

    def scanMyFiles(self):
        '''
        Scans the system for malware samples
        '''
        self._scanFiles=ScanFiles(self)