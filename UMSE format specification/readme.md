# UMSE Specification

UMSE format is formally specified using Kaitai Struct language.  

| File                  | Description                                                                |
| --------------------- |:--------------------------------------------------------------------------:|
| umse.ksy              | [Kaitai Struct](https://kaitai.io/) UMSE formal specification              |
| umse.bt               | [SweetScap 010Editor](https://www.sweetscape.com/010editor/) UMSE template |

A sample given in UMSE format consists in the following sub-structures:  

1. UMSE header  
![alt text](../Master%20Thesis/figures/UMSEHeader.png "UMSE header")  
2. Decryption table  
![alt text](../Master%20Thesis/figures/UMSEDT.png "Decryption table")  
3. Entries  
![alt text](../Master%20Thesis/figures/UMSEEntries.png "Entries")  
4. File properties  
![alt text](../Master%20Thesis/figures/UMSEFP.png "File properties")  
5. Authentication header  
![alt text](../Master%20Thesis/figures/UMSEAH.png "Authentication header")  
6. RSA Private key (this is an optional field)  
![alt text](../Master%20Thesis/figures/UMSEPK.png "RSA Private key")  
