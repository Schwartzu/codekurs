
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
	char source[51];
	char dest[51];
	int in;	
	char key[] = "KEY";


	code = read_text("enc.txt");
	res = vigenere(key, code, ENCODING);

	printf("%i\n", ggT_distances(distances(code), strlen(code)));

	free(res);
	free(code);

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