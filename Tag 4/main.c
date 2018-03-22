#include <stdio.h>

#include "utilities.h"
#include "textio.h"

#include "krypto.h"

int main(void)
{
	char test[] = "TEST";

	if(!is_text_upper_case(test))
		printf("String not uppercase!\n");
	else
		printf("String is uppercase!\n");

	return 0;
}