#include <assert.h>
#include <limits.h>
#include <math.h>

#include "intval.h"

int iqout_a(int n, int m)
{
	int u = 0;

	assert(n >= 0 && m > 0 && u == 0);
	assert(u * m <= n);

	while((u + 1) * m <= n){

		assert((u * m <= n));

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

		assert((u * m <= n) && (h == (u + 1) * m));

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

		assert(u * m <= n && n < o * m && u <= (o - 1));
	}

	assert(u * m <= n && n < o * m && u <= (o - 1) && u >= (o - 1));
	assert(u * m <= n && (u + 1) * m > n);

	return u;
}


int ilog_a(int n)
{
	int u = 0;

	assert(u == 0 && n > 0);
	assert(pow(2, u) <= n);

	while(pow(2, u + 1) <= n)
	{
		assert(pow(2, u) <= n);
		u++;
	}

	
	assert((pow(2, u) <= n) && (pow(2, u + 1) > n));

	return u;
}

int ilog_b(int n)
{
	int u = 0;
	int h = 2;

	assert(h == 2 && u == 0 && n > 0);
	assert(pow(2, u) <= n && h == pow(2, u + 1));

	while(h <= n)
	{
		assert(pow(2, u) <= n && h == pow(2, u + 1));
		u++;
		h *= 2;
	}

	assert(pow(2, u) <= n && h == pow(2, u + 1) && h > n);

	return u;
}

int ilog_c(int n)
{
	int u = 0;
	int o = n + 1;
	int a;

	assert(u == 0 && o == n + 1 && n > 0);
	assert(pow(2, u) <= n && pow(2, o > n) && u <= (o - 1));

	while(u < (o - 1))
	{
		assert(pow(2, u) <= n && pow(2, o) > n);

		a = (u + o) / 2;
		if(pow(2, a) <= n)
			u = a;
		else
			o = a;
	}

	assert(pow(2, u) <= n && pow(2, u + 1));

	return u;
}

int isqrt_a(int n)
{
	int u = 0;

	assert(n >= 0 && u == 0);
	assert(u * u <= n);

	while((u + 1) * (u + 1) <= n){

		assert(u * u <= n);

		u++;

		assert(u * u <= n);
	}

	assert((u * u <= n) && ((u + 1) * (u + 1) > n));

	return u;
}

int isqrt_b(int n)
{
	int u = 0;
	int h = 1;

	assert(u == 0 && n >= 0 && h == 1);
	assert(u * u <= n && h == (u + 1) * (u + 1));

	while(h <= n)
	{
		assert(u * u <= n && h == (u + 1) * (u + 1));

		u++;
		h = h + 2 * u + 1;

		assert(u * u <= n && h == (u + 1) * (u + 1));
	}

	assert(u * u <= n && (u + 1) * (u + 1) == h && h > n);

	return u;
}

int isqrt_c(int n)
{
	int u = 0;	
	int o = n + 1;
	int a;

	assert(u == 0 && o == n + 1 && n >= 0);
	assert(u * u <= n && o * o > n && u <= (o - 1));

	while(u < (o - 1))
	{
		assert(u * u <= n && o * o > n);

		a = (u + o) / 2;
		if(a * a <= n)
			u = a;
		else
			o = a;
		assert(u * u <= n && o * o > n);

	}
	assert(u * u <= n && o * o > n && u <= (o - 1) && u >= (o - 1));
	assert(u * u <= n && o * o >n);

	return u;
}