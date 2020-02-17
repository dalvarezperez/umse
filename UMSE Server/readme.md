# UMSE Intelligence Server

## UMSE Intelligence Server structure  

| File/s                 | Description                                                                                       |
| ---------------------- |:-------------------------------------------------------------------------------------------------:|
| favicon.ico            | The web application favicon.                                                                      |
| launch.bat             | Simple batch file to start the program.                                                           |
| libgcc_s_sheh-1.dll, libstdc++-6.dll, libwinpthread-1.dll       | libUmse.dll dependencies                                 |
| libUmse.dll            | The compiled UMSE C/C++ library.                                                                  |
| rsa_private_key.pem    | RSA Private key which allows UMSE sample parts decryption.                                        |
| server.py              | A Cherrypy server implementing an extremely simple intelligence webpage and REST API to allow the agent to operate with samples. Samples are stored in a SQLite database.|
| sqlitequeries.py       | SQLite queries are defined here.                                                                  |
| umse.py                | Kaitai Struct UMSE file format parser.                                                                    |  
| umsedecryptiontools.py | Python functions allowing to decrypt an UMSE entry (functionality is implemented by libUmse.dll. It is only a bridge to it).                                           |  
| tpl/samples.tpl        | HTML with JAVASCRIPT template used by Cherrypy.                                                   |  

## UMSE Intelligence Server Panel  

This is how intelligence panel looks like. It is extremely simple. Only sample listing (- and + are shortcut keys to go back and forward), sample search, and sample downloading features are implemented. But note that REST API requires authentication in order to decrypt samples, and every decryption operation is logged into SQLite database access logging table.  

![alt text](../Master%20Thesis/figures/UMSEPanel.png "UMSE Intelligence Server Panel")