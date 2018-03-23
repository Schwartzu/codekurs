#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "tsp.h"

int distance(int perm[], const int dist[], int len)
{
	int i;
	int sum = 0;
	int size = len - 1;

	assert(perm != NULL && dist != NULL && len > 0);

	for(i = 0; i < len; i++)
		sum += dist[perm[i] * size + perm[(i + 1) % len]];

	return sum;
}

void testopt(int perm[], const int dist[], int opt[], int len)
{
	int i;

	assert(perm != NULL && dist != NULL && opt != NULL && len > 0);

	if(distance(perm, dist, len) < distance(opt, dist, len))
		for(i = 0; i < len; i++)
			opt[i] = perm[i];

}

int next(int i, const int perm[], int len)
{
	int j;

	assert(i >= 0);
	assert(perm != NULL);
	assert(len > 0);

	for(j = i + 1; j < len; j++)
	{
		if(perm[j] == -1)
			return j;
	}

	return len;

}

int minimum(const int dist[], int len)
{
	int i, j;
	int res = INT_MAX;

	assert(dist != NULL && len > 0);

	for(i = 0; i < len; i++)
		for(j = 0; j < len; j++)
			if(i != j)
				if(dist[i * (len - 1) + i] < res)
					res = dist[i * (len - 1) + i];

	return res;
}

int distance_min(int perm[], const int dist[], int len)
{
	int i;
	int sum = 0;

	assert(perm != NULL && dist != NULL && len > 0);

	for(i = 0; i < len; i++)
	{
		if(perm[i] != -1 && perm[(i + 1) % len] != -1)
			sum += dist[perm[i] * len + perm[(i + 1) % len]];
		else
			sum += minimum(dist, len);
	}

	return sum;
}

void tsp(int perm[], int opt[], const int dist[], int depth, int len)
{
	int i = 0;

	assert(perm != NULL && opt != NULL && dist != NULL && depth >= 0 && len > 0);

	if(depth == len){
		testopt(perm, dist, opt, len);
	}
	else
	{
		while(i < len)
		{
			i = next(i, perm, len);
			perm[i] = depth + 1;
			if(distance_min(opt, dist, len) > distance(perm, dist, len))
				tsp(perm, opt, dist, depth + 1, len);
			perm[i] = -1;
		}

	}
}