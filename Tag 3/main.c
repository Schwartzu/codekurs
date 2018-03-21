#include <stdio.h>

#include "intval.h"

void print_func(int n, int m, int (*func)(int n, int m));

int main(void)
{
	int n = 20;
	int m = 6;

	print_func(n, m, iqout_a);
	print_func(n, m, iqout_b);
	print_func(n, m, iqout_c);

	return 0;
}

void print_func(int n, int m, int (*func)(int n, int m)){
	printf("func(%i, %i) = %i\n", n, m,  func(n, m));
}