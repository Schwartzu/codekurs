#include <stdio.h>
#include <math.h>

#include "approx.h"
#include "intval.h"

void print_quot(int n, int m, int (*func)(int n, int m));
void print_ilog(int n, int (*func)(int n));
void print_isqrt(int n, int (*func)(int n));
void print_euler(double eps);
void print_my_exp(double x, double eps);
void print_crt(double x, double eps);
void print_area(double a, double b, double eps, double (*func)(double x));


double f_2x(double x);
double f_x2(double x);
double f_x3(double x);


int main(void)
{
	int n = 13;
	int m = 3;

	double a = 2;
	double b = 1;

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

	putchar('\n');

	print_crt(27, 0.0001);

	putchar('\n');

	print_area(a, b, 0.000001, f_2x);

	print_area(a, b, 0.000001, f_x2);

	print_area(a, b, 0.000001, f_x3);



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

void print_crt(double x, double eps)
{
	printf("crt(%f, %lf) = %f\n", x, eps, crt(x, eps));
}

void print_area(double a, double b, double eps, double (*func)(double x))
{
	printf("area(%f, %f) = %f\n", a, b, calc_area(a, b, eps, func));
}

double f_2x(double x)
{
	return 2 * x;
}

double f_x2(double x)
{
	return x * x;
}

double f_x3(double x)
{
	return x * x * x;
}