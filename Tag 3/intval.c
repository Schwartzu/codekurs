#include <assert.h>
#include <limits.h>

#include "intval.h"

int iqout_a(int n, int m)
{
	int u = 0;

	assert( n >= 0 && m > 0 && u == 0);

	while((u + 1) * m <= n){

		assert((u * m <= n) && ((u + 1) * m <= n));

		if(u++ == INT_MAX)
			return -1;

		assert(u * m <= n);
	}

	assert((u * m <= n) && (u + 1) * m > n);

	return u;
}

int iqout_b(int n, int m)
{
	int u = 0;
	int h = m;

	assert(n >= 0 && m > 0 && u == 0 && h == m);
	assert((u * m <= n) && (h == (u + 1) * m));

	while(h <= n)
	{

		assert((u * m <= n) && (h <= n) && (h == (u + 1) * m));

		if(u++ == INT_MAX)
			return -1;

		assert((u * m <= n) && (h == u * m));

		if(INT_MAX - m < h)
			return -1;
		h += m;

		assert((u * m <= n) && (h == (u + 1) * m));
	}

	assert((u * m <= n) && (h == (u + 1) * m) && (h > n));
	assert((u * m <= n) && (u + 1) * m > n);

	return u;
}

int iqout_c(int n, int m)
{
	int u = 0;
	int o = n + 1;
	int a;

	assert(n >= 0 && m > 0 && u == 0 && o == n + 1);
	assert(u * m <= n && n < o * m && u <= (o - 1));

	if(INT_MAX == n)
		return -1;

	while(u < (o - 1))
	{
		assert(u * m <= n && n < o * m && u <= (o - 1));

		a = (u + o) / 2;
		if(a * m <= n)
			u = a;
		else
			o = a;

		assert(u * m<= n && n < o * m && u <= (o - 1));
	}

	assert(u * m <= n && n < o * m && u <= (o - 1) && u >= (o - 1));
	assert(u * m <= n && (u + 1) * m > n);

	return u;
}
