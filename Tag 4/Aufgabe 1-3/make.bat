cls
gcc -c krypto.c %c89%
gcc krypto.o textio.o utilities.o main.c %c89%