#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>


const double a(1);
const double b(35);
const double eps(1e-4);
const int size(100);

// function to approximate
double f(double x);

// return element of Chebyshev's polinom
double chebyshev(double x, int n);

// calculate element of normal system
double first_operand(double x, int n1, int n2);

// calculate free element of normal system
double second_operand(double x, int n);

// calculate integral using Simpson rule
double simpson_rule(double a, double b, double h, int n1, int n2 = -1);

// claculate integral with given precision
double integrate(double a, double b, double eps, int n1, int n2 = -1);

// solve normal system using Gauss method for SLAE
std::vector<double> gauss_method(std::vector<std::vector<double>> &matrix);

// prepare matrix before pass it through gauss method
void prepare_matrix(std::vector<std::vector<double>> &matrix, int n, double a, double b, double eps);

// claculate generalized polynomial
double calc_polynomial(std::vector<double> vect, double x);

// calculate power of x
double power(double x, int n);

// calculate standart deviation f(x) and p(x)
double std_dev(double a, double b, std::vector<double> alpha, double eps);

// print result to txt file
void print_res(double a, double b, std::vector<double> alpha, double eps, FILE *f1, FILE *f2);
