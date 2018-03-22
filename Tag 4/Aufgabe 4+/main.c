
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utilities.h"
#include "textio.h"

#include "krypto.h"

int main(void)
{
	char *code;
	char *res;
	char *key;
	char source[51];
	char dest[51];
	int in;	


	if((code = read_text("entschluessel_mich.txt")) == NULL)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		return 1;
	}
	if((key = kasiski(code)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		free(code);
		return 1;
	}
	printf("KASISKI: %s\n", key);

	if((res = vigenere(key, code, DECODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		free(code);
		return 1;
	}
	printf("%s\n", res);
	free(res);
	free(key);
	free(code);

	/*=============			test 		===============*/
	if((code = read_text("test.txt")) == NULL)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		return 1;
	}

	if((res = vigenere("VIER", code, ENCODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		free(code);
		return 1;
	}

	printf("KASISKI: %s\n", kasiski(res));
	printf("%s\n", vigenere(kasiski(res), res, DECODING));
	free(code);
	free(res);


	printf("Name der zu decodenden Datei (max 50 Zeichen): ");
	if(scanf("%50s", source) !=  1 || getchar() != '\n')
	{
		printf("Ungueltige Eingabe!\n");
		return 1;
	}

	printf("Zieldatei (max 50 Zeichen): ");
	if(scanf("%50s", dest) != 1 || getchar() != '\n')
	{
		printf("Ungueltige Eingabe!\n");
		return 1;

	}
	printf("<1> Bruteforce\n<2> Frequency Analysis\n\n<0> Beenden\n");
	if(scanf("%i", &in) !=  1 || getchar() != '\n')
	{
		printf("Ungueltige Eingabe!\n");
		return 1;
	}
	code = read_text(source);
	switch(in)
	{
		case 1:
			brute_caesar(code, dest);
			break;

		case 2:
			if((res = caesar(freq_analysis(code), code, DECODING)) == NULL)
			{
				printf("Fehler bei der Speicherreservierung!\n");
				free(code);
				return 1;
			}
			write_text(res, dest);
			free(res);
			break;
	}

	free(code);

	return 0;
}