//
// created 30.10.2016 by vlad.podilnyk
// numerical methods lab 3 
//
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <unordered_map>

const int columns(4);
const int size(4);


typedef struct {
	double item;
	int  row;
	int column;
} element;

typedef struct {
	double value;
	int var_number;
} root;
// function searchs the largest element in absolute value
element search_el(std::vector<std::vector<double>> &matrix);

// the main algorithm witch solves system of linear equations
std::vector<root> select(std::vector<std::vector<double>> &matrix, std::vector<double> &free_mem);

// 
void reset(std::vector<std::vector<double>> &matrix, int row, int column);

void transf(std::vector<std::vector<double>> &matrix, std::vector<double> m_vect, int main_row_indx);

std::vector<double> m_vect_calculate(std::vector<std::vector<double>> &matrix, element value);

std::vector<std::vector<double>> create_extended_matrix(std::vector<std::vector<double>> &matrix, std::vector<double> &free_mem);

// simple iteration method

std::vector<double> iter(std::vector<std::vector<double>> &a_matrix, std::vector<double> &b_coulmn, double eps);