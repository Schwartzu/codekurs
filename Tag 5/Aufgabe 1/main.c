#include <stdio.h>
#include <stdlib.h>

#include "backpack.h"

void allocerror(void);
void paramerror(void);

void print_info(const int res[], const Item items[],int n);

int main(int argc, char *argv[])
{
	int i;
	int cutoff;
	int *opt, *m;
	int n = argc - 2;
	Item *items;

	if(argc < 4)
	{
		paramerror();
		return 1;
	}

	cutoff = atoi(argv[1]);

	if(cutoff == 0)
	{
		paramerror();
		return 1;
	}

	opt = calloc(n, sizeof(int));
	if(opt == NULL)
	{
		allocerror();
		return 1;
	}

	m = calloc(n, sizeof(int));
	if(m == NULL)
	{
		allocerror();
		free(opt);
		return 1;
	}

	items = malloc((n) * sizeof(Item));
	if(items == NULL)
	{
		allocerror();
		free(opt);
		free(m);
		return 1;
	}

	for(i = 2; i < argc; i++)
	{
		items[i - 2].id = i - 1;
		items[i - 2].weight = atoi(argv[i]);
		if(items[i - 2].weight == 0)
		{
			paramerror();
			free(opt);
			free(items);
			free(m);
			return 1;
		}
	}

	backpack(m, opt, items, cutoff, 0, n);
	print_info(opt, items, n);


	free(opt);
	free(items);
	free(m);
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

void print_info(const int res[], const Item items[], int n)
{
	int i;
	int sum = 0;

	for(i = 0; i < n; i++)
	{
		if(res[i]){
			printf("id:%i\tweight: %i\n", items[i].id, items[i].weight);
			sum += items[i].weight;
		}
	}

	printf("Total sum: %i\n", sum);
}