#ifndef BACKPACK_H_INCLUDED
#define BACKPACK_H_INCLUDED

typedef struct _item{
	int id;
	int weight;
} Item;

int gewicht(int m[], const Item items[], const int n);

void testopt(int m[], const Item items[], int opt[], const int cutoff, const int n);

void backpack(int m[], int opt[], const Item items[], const int cutoff, const int depth, int n);


#endif