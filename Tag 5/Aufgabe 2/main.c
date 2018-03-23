#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tsp.h"

void allocerror(void);
void paramerror(void);

int ismirrored(int dist[], int len);
/**

	app.exe [DISTANCE_0_0] [DISTANCE_1_0] [DISTANCE_2_0] [DISTANCE_0_1] [DISTANCE_0_2]

*/
int main(int argc, char *argv[])
{
	int i, j;
	int *opt, *perm;
	int len = argc - 1;
	int sqrtlen = sqrt(len);
	int *dist;

	if(argc < 4)
	{
		printf("Too few arguments!\n");
		return 1;
	}
	if(sqrt(len) != floor(sqrt(len)))
	{
		printf("Distances is not squared!\n");
		return 1;
	}

	dist = malloc((len) * sizeof(int));
	if(dist == NULL)
	{
		allocerror();
		return 1;
	}

	for(i = 0; i < argc - 1; i++){
		if((dist[i] = atoi(argv[i + 1])) == 0)
		{
			printf("Only numbers are vaild!\n");
			free(dist);
			return 1;
		}
		if(!(i % sqrtlen))
			putchar(10);
		printf("%i ", dist[i]);
	}
	putchar(10);

	if(!ismirrored(dist, sqrtlen))
	{
		printf("Distances aren't mirrored!\n");
		free(dist);
		return 1;
	}

	opt = malloc(len * sizeof(int));
	if(opt == NULL)
	{
		allocerror();
		free(dist);
		return 1;
	}

	for(i = 0; i < len; i++)
		opt[i] = i;

	perm = malloc(len * sizeof(int));
	if(perm == NULL)
	{
		allocerror();
		free(opt);
		free(dist);
		return 1;
	}
	memset(perm, -1, len * sizeof(int));

	tsp(perm, opt, dist, 0, sqrtlen);

	for(i = 0; i < len; i++)
	{
		printf("%i ", i);
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

int ismirrored(int dist[], int len)
{
	int i, j;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			if(dist[i * len + j] != dist[j * len + i])
				return 0;
		}
	}

	return 1;
}