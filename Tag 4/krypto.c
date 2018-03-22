#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

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