# UMSE Implementation

A C/C++ library was developed to work more easily with UMSE. As most of security products are developed in C/C++, the UMSE library was developed in these languages but note that it can be used with independence of the programming language, for instance, the author integrated it with Python and, obviously, it worked.  

## UMSE library project follows a standard C project structure  

| Directory | Description                                                                                            |
| --------- |:------------------------------------------------------------------------------------------------------:|
| bin       | Compiled resulting binaries are putted inside this directory.                                          |
| build     | Building files are putted in this directory.                                                           |
| doc       | Documentation directory.                                                                               |
| include   | Includes are here. A subfolder named include also exists and it is used to store third party includes. |
| lib       | Library files are stored here.                                                                         |
| src       | The program source code.                                                                               |
| test      | Some code to test the library.                                                                         |  


## Project content  

| Element                | Description                                                                                            |
| ---------------------- |:------------------------------------------------------------------------------------------------------:|
| parsers directory      | Contains a lot of common file type parsers for C++. These parsers were generated automatically by Kaitai Struct. Parsers folder includes also umse.cpp in order to demonstrate that UMSE specification works as expected and it is implemented. |
| conversion directory   | Implements the conversion from every specific file format or chunk structure to UMSE. In file headers of each file format/chunk structure converter are defined parameters to calculate the corresponding confidentiality level of each file part. |
| umseUtils.c file       | All necessary functions to deal with UMSE format are developed here. It is not dependent from Kaitai Struct in order to allow you to re-use it in other projects. |
| main.cpp file          | UMSE library exported functions are written here and some testing/debugging code is also written here. |

This is how it looks like in [Code::Blocks](http://www.codeblocks.org/)  

![alt text](../Master%20Thesis/figures/UMSEProject.png "UMSE Project")  


## How to configure Code::Blocks to work with UMSE  

### GNU GCC Compiler

Go to settings -> Compiler

1. Compiler settings -> Compiler options  
`` -fpermissive ``  

2. Compiler settings -> Defines  
``BUILD_DLL``  
``DEBUG``  
``_DEBUG``  

3. Linker settings -> Link libraries  
``{PROJECT_DIRECTORY}\libUmse\include\include\openssl-1.1.1\lib\libcrypto.a``  
``{PROJECT_DIRECTORY}\libUmse\include\include\openssl-1.1.1\lib\libssl.a``  

4. Linker settings -> Other linker options  
`` -llibssl -llibcrypto ``  

5. Search directories -> Compiler  
``{PROJECT_DIRECTORY}\libUmse ``  
``{PROJECT_DIRECTORY}\libUmse\include\include\parsers ``  
``{PROJECT_DIRECTORY}\libUmse\include\include\parsers\kaitai ``  
``{PROJECT_DIRECTORY}\libUmse\include\include\openssl-1.1.1\include ``  

6. Search directories -> Linker  
``{PROJECT_DIRECTORY}\libUmse``  
``{PROJECT_DIRECTORY}\include\include\openssl-1.1.1\lib``  

7. Toolchain executables  
Compiler's installation directory: 
``C:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64``  
C compiler: 
``x86_64-w64-mingw32-gcc.exe``  
Linker for dynamic libs: 
``x86_64-w64-mingw32-g++.exe``  
Linker for static libs: 
``ar.exe``  
Debugger: 
``GDC/CDB Debugger : Default``  
Resource compiler: 
``windres.exe``  
Make program: 
``mingw32-make.exe``  

### Debugging settings

1. Project -> Set programs' arguments...  

* Debug profile:  
Program arguments: 
``{PROJECT_DIRECTORY}\libUmse\bin\Debug\libUmse.dll,DllMain``  
Host application: 
``C:\Windows\System32\rundll32.exe``  

* Release profile:  
Program arguments: 
``{PROJECT_DIRECTORY}\libUmse\bin\Release\libUmse.dll,DllMain``  
Host application: 
``C:\Windows\System32\rundll32.exe``  
