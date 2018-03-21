#include <stdio.h>
#include <math.h>

#include "approx.h"
#include "intval.h"

void print_quot(int n, int m, int (*func)(int n, int m));
void print_ilog(int n, int (*func)(int n));
void print_isqrt(int n, int (*func)(int n));
void print_euler(double eps);
void print_my_exp(double x, double eps);



int main(void)
{
	int n = 13;
	int m = 3;

	double dexp = 10;

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

	putchar('\n');

	print_euler(0.000001);

	putchar('\n');

	print_my_exp(dexp, 0.000001);

	printf("stdexp(%f) = %f\n", dexp, exp(dexp));

	putchar('\n');


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


void print_euler(double eps)
{
	printf("euler(%f) = %f\n", eps, euler(eps));
}

void print_my_exp(double x, double eps)
{
	printf("my_exp(%f, %lf) = %f\n", x, eps, my_exp(x, eps));
}