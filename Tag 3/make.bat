cls
gcc -c intval.c -ansi -pedantic -Wall -Wextra
gcc -c approx.c -ansi -pedantic -Wall -Wextra
gcc intval.o approx.c main.c -ansi -pedantic -Wall -Wextra