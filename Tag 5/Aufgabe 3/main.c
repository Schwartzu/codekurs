#include <stdio.h>
#include <stdlib.h>

#include "damen.h"

int main(int argc, char *argv[])
{
	int n;
	int res;
	int *brett;

	if(argc != 2 || !(n = atoi(argv[1])))
	{
		printf("Invalid arguments!\n");
		return 1;
	}

	brett = calloc(n, sizeof(int));

	if((res = dame(brett, n)) == -1)
	{
		printf("Fehler bei der berechnung!\n");
		free(brett);
		return 1;
	}

	printf("Es gibt %i viele Loesungen!\n", res);

	free(brett);

	return 0;
}