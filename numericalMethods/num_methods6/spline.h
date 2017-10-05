#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>


const double a(1.0);
const double b(35.0);
const double eps(1e-4);

// function to approximate
double f(double x);

// calculate A coef
std::vector<double> calc_A(double a, double b, int N);

// calculate B coef
std::vector<double> calc_B(std::vector<double> C, std::vector<double> D, double a, double b, int N);

// calculate C coef
std::vector<double> calc_C(double a, double b, int N);

// calculate D coef
std::vector<double> calc_D(std::vector<double> C, double a, double b, int N);

// prepare matrix
void prepare_matrix(std::vector<std::vector<double>> &matrix, int N, double a, double b);

// Gauss method for SLAE
std::vector<double> gauss_method(std::vector<std::vector<double>> &matrix);

// return value of Si
double s_i(double x, std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D, double a, double b, int N);

// print table with x and y coordinates
void plot_spline(double a, double b, int N, FILE *f1, FILE *f2);
