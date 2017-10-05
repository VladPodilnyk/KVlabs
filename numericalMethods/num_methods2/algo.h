//
// created by Vlad Podilnyk 26.10.2016 
//

#pragma once
#include <stdio.h>
#include <math.h>

#define epsLimit 1e-14

typedef struct {
	double res;
	double precision; 
	int counter;
} result;

double phi(double x1, double lambda);

double func(double x, char choice);

result iter(double a, double b, double eps);

result tangent(double a, double b, double eps);