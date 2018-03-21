#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "approx.h"


double calc_frac(double x, int n)
{
	double res = 1;
	int i;

	for(i = 0; i < n; i++){
		res *= x / (n - i);

	}

	return res;
}

double euler(double eps)
{
	int i;
	double res = 0;

	for(i = 0; fabs(eps) < fabs(2 * calc_frac(1, i + 1)); i++)
		res += calc_frac(1, i);

	return res;
	
}

double my_exp(double x, double eps)
{
	double res = 0;
	int i = 0;

	for(i = 0;; i++)
	{
		if((fabs(x) <= 1 + 0.5 * i)){
			if(!(fabs(eps) < fabs(2 * calc_frac(x, i + 1))))
				break;
		}
		res += calc_frac(x, i);

	
	}

	return res;
}

double crt(double a, double eps)
{
	double x_alt = 1, x = (2 + a) / 3;

	while(fabs(x - x_alt) > eps)
	{	
		x_alt = x;
		x = (2 * x + (a / (x * x))) / 3;
	}

	return x;

}

double calc_area(double a, double b, double eps, double (*f)(double))
{
	int i, j;
	double area, area_old = INT_MAX;

	for(i = 1;; i *= 2)
	{
		area = 0;
		for(j = 1; j <= i; j++){
			area += fabs(f(a + (j - 1) * ((b - a) / i)) * ((b - a) / i));
		}
		if(fabs(area - area_old) <= eps)
			break;
		area_old = area;
	}

	return area;
}