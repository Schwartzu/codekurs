#include <stdlib.h>

#include "utilities.h"

int my_comparator(const void *a, const void *b)
{
	if (((struct sub_dist *)a)->frequency > ((struct sub_dist *)b)->frequency)
		return -1;
	else if (((struct sub_dist *)a)->frequency == ((struct sub_dist *)b)->frequency)
		return 0;
	else
		return 1;
}

int *sort_array(const int *array, int size_of_array, int number)
{
	int i = 0;
	int *output;
	struct sub_dist *dists = malloc(size_of_array * sizeof(struct sub_dist));
	if (dists == NULL)
		return NULL;
	output = malloc(number * sizeof(int));
	if (output == NULL) {
		free(dists);
		return NULL;
	}
	for (i = 0; i < size_of_array; ++i) {
		dists[i].distance = i;
		dists[i].frequency = array[i];
	}
	qsort(dists, size_of_array, sizeof(struct sub_dist), my_comparator);
	for (i = 0; i < number; ++i)
		output[i] = dists[i].distance;
	free(dists);
	return output;
}

int euklid(int a, int b)
{
	int help;
	do {
		help = a % b;
		a = b;
		b = help;
	} while (help != 0);
	return a;
}
