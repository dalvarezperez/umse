# UMSE Agent

The UMSE Agent is an extremely simple Python program to demonstrate how to collect system elements, transform it to UMSE, and sent the resulting UMSE samples to a central intelligence server.  

![alt text](../Master%20Thesis/figures/UMSEAgent.png "UMSE Agent")  

UMSE agent is composed of the following files:

| Files                 | Purpose                                                         |
| --------------------- |:---------------------------------------------------------------:|
| aboutform.py          | A simple form showing information about the program.            |
| av agent.py           | PyQt5 System Tray Icon entrypoint.                              |
| intelligenceclient.py | REST API functions for communicating with UMSE Server.          |
| scanfiles.py          | Element collector, UMSE conversion and sending via libUmse.dll. |
| trayicon.py           | System Tray Icon implementation.                                |  



The agent must to be launched as follows:  
``
start /D . C:\Python\Python37\pythonw.exe av_agent.py
``
