#include "spline.h"

double f(double x) {
	return log10(x * x) * sin(x / 2.0) * exp(pow(x, 1 / 7.0));
}

std::vector<double> calc_A(double a, double b, int N) {
	std::vector<double> result(N);
	double h = (b - a) / double(N - 1);
	double x = a;
	for (int i = 0; i < N; ++i) {
		result[i] = f(x);
		x += h;
	}
	return result;
}


void prepare_matrix(std::vector<std::vector<double>> &matrix, int N, double a, double b) {
	matrix.resize(N);
	int columns  = N + 1;
	double h = (b - a) / double(N - 1);
	double fcurr, fprev, fnext;
	for (int i = 0; i < N; ++i)
		matrix[i].resize(columns);

	matrix[0][0] = 1;
	matrix[N - 1][N - 1] = 1;
	int n = N - 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (i == j)
				matrix[i][j] = 2 * h;
			else if ((i - 1) == j || (i + 1) == j)
				matrix[i][j] = h;
			else if (j == N) {
				fprev = f(a + h * (i - 1));
				fcurr = f(a + h * i);
				fnext = f(a + h * (i + 1));
				matrix[i][j] = 6 * (fnext - 2 * fcurr + fprev) / h;
			}
			else
				matrix[i][j] = 0;
		}
	}
}



std::vector<double> gauss_method(std::vector<std::vector<double>> &matrix){
	int k = 0;
	int columns = matrix[0].size();
	int n = matrix.size();
	int free_el = columns - 1;
	double A;
	std::vector<double> tmp;
	std::vector<double> result(n);

	while (k < n) {
		A = matrix[k][k]; // diagonal element 
		for (int col = 0; col < columns; ++col)
			matrix[k][col] = matrix[k][col] / A;

		for (int i = 0; i < n; ++i) {
			if (i == k)
				continue;
			tmp = matrix[k];
			std::transform(tmp.begin(), tmp.end(), tmp.begin(),
				std::bind1st(std::multiplies<double>(), matrix[i][k]));

			std::transform(matrix[i].begin(), matrix[i].end(), tmp.begin(), matrix[i].begin(), std::minus<double>());
		}
		++k;
	}

	for (int i = 0; i < n; ++i)
		result[i] = matrix[i][free_el];

	return result;
}


std::vector<double> calc_C(double a, double b, int N) {
	std::vector<std::vector<double>> matrix;
	std::vector<double> result;
	prepare_matrix(matrix, N, a, b);
	result = gauss_method(matrix);
	return result;
}


std::vector<double> calc_D(std::vector<double> C, double a, double b, int N) {
	std::vector<double> D(N);
	double h = (b - a) / double(N - 1);
	D[0] = C[0];
	for (int i = 1; i < N; ++i) 
		D[i] = (C[i] - C[i - 1]) / h;

	return D;
}


std::vector<double> calc_B(std::vector<double> C, std::vector<double> D, double a, double b, int N) {
	std::vector<double> B(N);
	double h = (b - a) / double(N - 1);
	double fcurr, fprev;
	B[0] = 0;
	for (int i = 1; i < N; ++i) {
		fcurr = a + h * i;
		fprev = a + h * (i - 1);
		B[i] = h * C[i] / 2 - h * h * D[i] / 6 + (fcurr - fprev) / h;
	}
	return B;
}


double s_i(double x, std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D, double a, double b, int N) {
	double h = (b - a) / double(N - 1);
	int i = 0;
	double xi = a + i * h;
	double res, delta;
	while (x > xi) {
		++i;
		xi = a + i * h;
	}
	//--i;
	//Sxi = a + i * h;
	delta = x - xi;
	res = A[i] + B[i] * delta + C[i] * delta * delta / 2 + D[i] * delta * delta * delta / 6;
	return res;
}


void plot_spline(double a, double b, int N, FILE *f1, FILE *f2) {
	double h = (b - a) / double(N - 1);
	double x, y;
	std::vector<double> A = calc_A(a, b, N);
	std::vector<double> C = calc_C(a, b, N);
	std::vector<double> D = calc_D(C, a, b, N);
	std::vector<double> B = calc_B(C, D, a, b, N);
	x = a + h;
	for (int i = 1; i < N; ++i) {
		y = s_i(x, A, B, C, D, a, b, N);
		fprintf(f1, "%.3g\n", x);
		fprintf(f2, "%.3g\n", y);
		x += h;	
	}
}