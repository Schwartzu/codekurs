#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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