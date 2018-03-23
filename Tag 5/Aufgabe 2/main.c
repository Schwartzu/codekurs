#include <stdio.h>
#include <stdlib.h>

#include "tsp.h"

void allocerror(void);
void paramerror(void);

int main(void)
{
	int *opt, *perm;
	int len = 3;
	int *dist;

	opt = calloc(len, sizeof(int));
	if(opt == NULL)
	{
		allocerror();
		return 1;
	}

	perm = calloc(len, sizeof(int));
	if(perm == NULL)
	{
		allocerror();
		free(opt);
		return 1;
	}

	dist = calloc(len * len, sizeof(int));
	if(dist == NULL)
	{
		allocerror();
		free(opt);
		free(perm);
		return 1;
	}




	free(opt);
	free(perm);
	free(dist);

	return 0;
}

void allocerror(void)
{
	printf("Fehler bei der Speicherallokierung!\n!");
}

void paramerror(void)
{
	printf("Ungueltige Paramter!\n");
}