#include <stdlib.h>
#include <assert.h>

#include "backpack.h"

int gewicht(int m[], const Item items[], const int n)
{
	int i;
	int res = 0;

	assert(m != NULL && items != NULL && n > 0);

	for(i = 0; i < n; i++){
		res += m[i] * items[i].weight;
	}

	return res;
}

void testopt(int m[], const Item items[], int opt[], const int cutoff, const int n)
{
	int i;

	assert(m != NULL && opt != NULL && items != NULL && n > 0);

	if(gewicht(m, items, n) <= cutoff && gewicht(m, items, n) > gewicht(opt, items, n))
	{
		for(i = 0; i < n; i++)
			opt[i] = m[i];
	}
}

void backpack(int m[], int opt[], const Item items[], const int cutoff, const int depth, int n)
{
	assert(m != NULL && opt != NULL && items != NULL && cutoff > 0 && depth >= 0 && n > 0);
	if(depth == n)
		testopt(m, items, opt, cutoff, n);
	else
	{
		m[depth] = 1;
		backpack(m, opt, items, cutoff, depth + 1, n);

		m[depth] = 0;
		backpack(m, opt, items, cutoff, depth + 1, n);
	}
}