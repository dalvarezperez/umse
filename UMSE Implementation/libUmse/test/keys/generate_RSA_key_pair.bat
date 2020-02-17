@echo off
rem Privare key:
openssl genrsa -out private_key.pem 2048

rem Public key:
openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048

rem Extract public key:
openssl rsa -pubout -in private_key.pem -out public_key.pem

@echo on
rem show elements

rem Private key:
openssl rsa -text -in private_key.pem

rem Public key:
type public_key.pem