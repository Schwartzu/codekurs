#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

struct sub_dist {
	int distance;
	int frequency;
};

int *sort_array(const int *array, int size_of_array, int number);
int euklid(int a, int b);

#endif
