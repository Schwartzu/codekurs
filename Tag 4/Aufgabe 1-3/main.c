#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "textio.h"

#include "krypto.h"

int main(void)
{
	char test[] = "HASTDUDICHHEUTESCHONGEAERGERTWARESHEUTEWIEDERSCHLIMMHASTDUDICHWIEDERMALGEFRAGTWARUMKEINMENSCHWASUNTERNIMMTDUMUSSTNICHTAKZEPTIERENWASDIRUEBERHAUPTNICHTPASSTWENNDUDEINENKOPFNICHTNURZUMTRAGENEINERMUETZEHASTESISTNICHTDEINESCHULDDASSDIEWELTISTWIESIEISTESWAERNURDEINESCHULDWENNSIESOBLE";
	char ckey = 'C';
	char key[] = "KEY";
	char *in, *res;

	if(!isupper(ckey))
	{
		printf("Ungueltiger Schluessel!\n");
		return 1;
	}
	if(!is_text_upper_case(test))
	{
		printf("Nur Grossbuchstaben!\n");
		return 1;
	}
	if((res = caesar(ckey, test, ENCODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung\n");
		return 1;
	}

	printf("Caesar:\n");
	printf("Original:\t%s\n", test);
	printf("Encoded:\t%s\n", res);
	printf("Decoded:\t%s\n", caesar(ckey, res, DECODING));

	printf("=========================================\n");
	
	free(res);

	in = read_text("test.txt");
	if(in == NULL)
	{
		printf("Fehler bei der Speicherreservierung\n");
		free(in);
		return 1;
	}
	if(!is_text_upper_case(key))
	{
		printf("Ungueltiger Schluessel!\n");
		free(in);
		return 1;
	}
	if((res = vigenere(key, in, ENCODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung\n");
		free(in);
		return 1;
	}

	write_text(res, "enc.txt");

	free(in);
	free(res);

	in = read_text("enc.txt");

	if((res = vigenere(key, in, DECODING)) == NULL)
	{
		printf("Fehler bei der Speicherreservierung\n");
		free(in);
		return 1;
	}

	write_text(res, "dec.txt");


	free(in);
	free(res);

	return 0;
}