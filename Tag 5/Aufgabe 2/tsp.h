#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

int distance(int perm[], const int dist[], int len);

void testopt(int perm[], const int dist[], int opt[], int len);

int next(int i, const int perm[], int len);

int minimum(const int dist[], int len);

int distance_min(int perm[], const int dist[], int len);

void tsp(int perm[], int opt[], const int dist[], int depth, int len);

#endif