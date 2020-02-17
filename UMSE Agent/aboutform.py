#!/usr/bin/env python
# -*- coding: UTF-8 -*-

"""
*  UMSE Antivirus Agent Example
*  Author: David Alvarez Perez <dalvarezperez87[at]gmail[dot]com>
*  Module: About Form
*  Description: This module launches the "UMSE Antivirus Agent Example" form.
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

from PyQt5 import QtWidgets, QtGui
from PyQt5.QtCore import Qt

class AboutForm(QtWidgets.QDialog):
    
    def __init__(self, parent=None):
        QtWidgets.QDialog.__init__(self, parent=None) 
        contenedor = QtWidgets.QVBoxLayout()
        self.setLayout(contenedor)

        # Logo image.
        self.mysqlPic = QtWidgets.QLabel(self)
        self.mysqlPic.setGeometry(30, 0, 100, 85)
        self.mysqlPic.setPixmap(QtGui.QPixmap("resources\\logo.png").scaled(50, 50, Qt.KeepAspectRatio, Qt.SmoothTransformation))

        # Label "UMSE Antivirus Agent Example".
        self.targetPath = QtWidgets.QLabel('<b>UMSE Antivirus Agent Example.</b>', self)
        self.targetPath.setGeometry(80, 0, 320, 50)
        self.targetPath.setObjectName("Antivirus")

        #Label "Copyrigth".
        self.targetPath = QtWidgets.QLabel('Copyrigth 2019-2020 UMSE Antivirus Agent Example<br>All rights reserved.', self)
        self.targetPath.setGeometry(80, 0, 320, 100)
        self.targetPath.setObjectName("Copyrigth")

        #Label "Information".
        self.targetPath = QtWidgets.QLabel('<b>Version:</b> 1.0.0 Beta<br><br>' + \
                                       'More information here: ' + \
                                       "<a href='https://github.com/dalvarezperez/umse'>https://github.com/dalvarezperez/umse</a>", self)
        self.targetPath.setGeometry(30, 0, 380, 280)
        self.targetPath.setObjectName("Information")

        #Show form.
        QtWidgets.QToolTip.setFont(QtGui.QFont('SansSerif', 10))
        self.resize(440, 220)
        self.center()
        self.setWindowTitle('About UMSE Antivirus Agent Example.')       
        self.show()

    def closeEvent(self, event):
        event.ignore()
        self.setProperty("visible", False)

    def center(self):
        qr = self.frameGeometry()
        cp = QtWidgets.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
