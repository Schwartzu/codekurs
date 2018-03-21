#ifndef APPROX_H_INCLUDED
#define APPROX_H_INCLUDED

double calc_frac(double x, int n);
double euler(double eps);
double my_exp(double x, double eps);

double crt(double a, double eps);

double calc_area(double a, double b, double eps, double (*f)(double));

#endif