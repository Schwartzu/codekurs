#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "textio.h"

#include "krypto.h"

int main(void)
{
	char test[] = "ABCDEFGHIJKLMNOPQRSTUVQXYZ";
	char key = 'T';
	char *res;

	if(!isupper(key))
	{
		printf("Ungueltiger Schluessel!\n");
		return 1;
	}
	if(!is_text_upper_case(test))
	{
		printf("Nur Grossbuchstaben!\n");
		return 1;
	}
	if((res = caesar(key, test, ENCODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung\n");
		return 1;
	}

	putchar('\n');
	printf("Original:\t%s\n", test);
	printf("Encoded:\t%s\n", res);
	printf("Decoded:\t%s\n", caesar(key, res, DECODING));

	free(res);

	return 0;
}