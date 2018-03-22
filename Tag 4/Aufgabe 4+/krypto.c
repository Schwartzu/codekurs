#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "krypto.h"
#include "textio.h"
#include "utilities.h"

int is_text_upper_case(const char *text)
{
	int i;

	assert(text != NULL);

	for(i = 0; text[i] != '\0'; i++){
		if(!isupper(text[i]))
			return 0;
	}

	return 1;
}

char *caesar(char key, const char *text, int coding_mode)
{
	int i;
	int len;
	char aKey;
	char *res;

	assert(is_text_upper_case(text));
	assert(isupper(key));
	assert(coding_mode == DECODING || coding_mode == ENCODING);

	aKey = key - 'A';
	len = strlen(text);

	res = malloc(len + 1);
	if(res == NULL)
		return NULL;

	if(coding_mode == ENCODING)
		for(i = 0; i < len; i++)
			res[i] = ((text[i] - 'A' + aKey) % 26) + 'A';
	else
		for(i = 0; i < len; i++)
			res[i] = ((text[i] - 'A' - aKey < 0 ? (text[i] - aKey + 26) : (text[i] - aKey)));
	
	res[i] = '\0';

	return res;
}

char *vigenere(const char *key, const char *text, int coding_mode)
{
	int i, j = 0;
	int len;
	int keylen;
	char *res;

	assert(is_text_upper_case(key) && is_text_upper_case(text) && (coding_mode == DECODING || coding_mode == ENCODING));

	len = strlen(text);
	keylen = strlen(key);

	res = malloc(len + 1);
	if(res == NULL)
		return NULL;

	if(coding_mode == ENCODING)
		for(i = 0; i < len; i++){
			res[i] = ((text[i] - 'A' + key[j] - 'A') % 26) + 'A';
			if(++j >= keylen)
				j = 0;
		}
	else
		for(i = 0; i < len; i++){
			res[i] = (text[i] - 'A' - (key[j] - 'A')) < 0 ? (text[i] - (key[j] - 'A') + 26) : (text[i] - (key[j] - 'A'));
			if(++j >= keylen)
				j = 0;
		}
	
	res[i] = '\0';

	return res;
}

void brute_caesar(const char *code, char *file)
{
	int i;
	int n;
	char in;
	char *res;
	char *buf;
	char *pre;

	assert(is_text_upper_case(code) && file != NULL);

	printf("Laenge des Praefix: ");
	if(scanf("%i", &n) != 1 || getchar() != '\n')
	{
		printf("Ungueltige Eingabe!\n");
		while(getchar() != '\n'){}
		return;
	}
	
	if(n <= 0)
	{
		printf("Nur ganze positive Zahlen!\n");
		return;
	}

	if((pre = malloc(n + 1)) == NULL)
		return;


	strncpy(pre, code, n);
	pre[n] = 0;

	for(i = 0; i < 26; i++)
	{

		if((buf = caesar('A' + i, pre, DECODING)) == NULL){
			printf("Fehler bei der Speicherreservierung!\n");
			return;
		}

		printf("Key %c:\t%s\n", i + 'A', buf);

		free(buf);

		printf("Soll dieser Schluessel verwendet werden? (j/n): ");
		
		in = getchar();

		if(getchar() != '\n'){
			while(getchar() != '\n'){}
			printf("Ungueltige Eingabe!\n");
			free(pre);
			return;
		}

		switch(in)
		{
			case 'j':
				if((res = caesar('A' + i, code, DECODING)) == NULL)
				{
					printf("Fehler bei der Speicherreservierung!\n");
					free(pre);
					return;
				}
				if((buf = malloc(strlen(file) + 5)) == NULL)
				{
					printf("Fehler bei der Speicherreservierung!\n");
					free(pre);
					return;
				}
				write_text(res, file);
				free(buf);
				free(res);
				return;

			case 'n':
				continue;

			default:
				printf("Ungueltige Eingabe!\n");
				free(pre);
				return;
		}
	}

	printf("Das wars!\n");
	free(pre);
	return;
}

char freq_analysis(const char *code)
{
	int i;
	int counter[26] = {0};
	int pos = 0;

	assert(is_text_upper_case(code));

	for(i = 0; i < (int) strlen(code); i++)
		counter[code[i] - 'A']++;

	for(i = 0; i < 26; i++){
		/*printf("%c(%i): %i\n", i + 'A', i, counter[i]);*/
		pos = (counter[i] > counter[pos] ? i : pos);
	}

	pos = ((pos + 'A') - 'E' < 0 ? pos - ('E' - 'A') + 26 + 'A' : pos - ('E' - 'A') + 'A');
	return pos;
}

int *distances(const char *code)
{
	int i, j;
	int *res;
	char *ptr;
	char cmpr[8];

	assert(is_text_upper_case(code));

	if((res = malloc(strlen(code) * sizeof(int))) == NULL)
		return NULL;

	for(i = 0; i < (int) strlen(code); i++)
		res[i] = 0;

	for(j = 3; j < 8; j++){
		for(i = 0; i < (int) strlen(code) - j; i++)
		{
			strncpy(cmpr, code + i, j);
			cmpr[j] = '\0';
			ptr = strstr(code + i + j, cmpr);
			if(ptr != NULL)
			{
				res[ptr - (code + i)]++;
			}
		}
	}
	return res;
}

int ggT_distances(const int *distances, int n)
{
	int i;
	int *sorted;
	int cur;

	assert(distances != NULL && n > 0);

	sorted = sort_array(distances, n, SYMBOL_N);

	cur = sorted[0];

	for(i = 0; i < SYMBOL_N - 1; i++)
	{
		printf("%i: ggt(%i, %i) = %i\n", i, sorted[i + 1], cur, euklid(sorted[i + 1], cur));	
		cur = euklid(sorted[i + 1], cur);
	}

	free(sorted);
	return cur;
}