#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
typedef struct {
	double value;
	double h;
}element;

double func(double x);

double trapezium_method(double a, double b, double &h);

element trapezium_method_dc(double a, double b, double eps);

