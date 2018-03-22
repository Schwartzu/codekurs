#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "krypto.h"


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

	assert(is_text_upper_case(text) && isupper(key) && (coding_mode == DECODING || coding_mode == ENCODING));

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

	assert(is_text_upper_case(key) && is_text_upper_case(text) && isupper(key) && (coding_mode == DECODING || coding_mode == ENCODING));

	len = strlen(text);
	keylen = strlen(key);

	res = malloc(len + 1);
	if(res == NULL)
		return NULL;

	if(coding_mode == ENCODING)
		for(i = 0; i < len; i++){
			res[i] = ((text[i] - 'A' + key[j] - 'A') % 26) + 'A';
			if(++j > keylen)
				j = 0;
		}
	else
		for(i = 0; i < len; i++){
			res[i] = ((text[i] - 'A' - key[j] - 'A' < 0 ? (text[i] - key[j] - 'A' + 26) : (text[i] - key[j] - 'A')));
			if(++j > keylen)
				j = 0;
		}
	
	res[i] = '\0';

	return res;
}