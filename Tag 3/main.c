#include <stdio.h>

#include "intval.h"

void print_quot(int n, int m, int (*func)(int n, int m));
void print_ilog(int n, int (*func)(int n));
void print_isqrt(int n, int (*func)(int n));

int main(void)
{
	int n = 13;
	int m = 3;

	print_quot(n, m, iqout_a);
	print_quot(n, m, iqout_b);
	print_quot(n, m, iqout_c);

	putchar('\n');

	print_ilog(n, ilog_a);
	print_ilog(n, ilog_b);
	print_ilog(n, ilog_c);
	
	putchar('\n');

	print_isqrt(n, isqrt_a);
	print_isqrt(n, isqrt_b);
	print_isqrt(n, isqrt_c);

	return 0;
}

void print_quot(int n, int m, int (*func)(int n, int m))
{
	printf("iquot(%i, %i) = %i\n", n, m,  func(n, m));
}

void print_ilog(int n, int (*func)(int n))
{
	printf("ilog(%i) = %i\n", n, func(n));
}

void print_isqrt(int n, int (*func)(int n))
{
	printf("isqrt(%i) = %i\n", n, func(n));
}
