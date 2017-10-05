#include "helpers.h"


double f(double x) {
	return log10(x * x) * sin(x / 2.0) * exp(pow(x, 1 / 7.0));
}


double chebyshev(double x, int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	double T_prev = 1;
	double T_curr = x;
	double tmp;

	for (int i = 2; i <= n; ++i) {
		tmp = T_curr;
		T_curr = 2 * x * T_curr - T_prev;
		T_prev = tmp;
	}
	return T_curr;
}

double first_operand(double x, int n1, int n2) {
	return chebyshev(x, n1) * chebyshev(x, n2);
}

double second_operand(double x, int n) {
	return f(x) * chebyshev(x, n);
}


double simpson_rule(double a, double b, double h, int n1, int n2) {
	int n = (int)((b - a) / h);
	h = (b - a) / n;
	double result = 0;

	double x0 = a;
	double x1 = a + h;
	double half_h = h / 2.0;
	if (n2 != -1) {
		for (int i = 0; i <= n - 1; ++i) {
			result += first_operand(x0, n1, n2) + 4.0 * first_operand(x0 + half_h, n1, n2) + first_operand(x1, n1, n2);
			x0 += h;
			x1 += h;
		}
	}
	else {
		for (int i = 0; i <= n - 1; ++i) {
			result += second_operand(x0, n1) + 4.0 * second_operand(x0 + half_h, n1) + second_operand(x1, n1);
			x0 += h;
			x1 += h;
		}
	}
	return (h / 6.0) * result;
}

double integrate(double a, double b, double eps, int n1, int n2) {
	double h = sqrt(sqrt(eps));
	double result;
	double curr_sum = 0;

	if (n2 == -1) {
		result = simpson_rule(a, b, h, n1);
		// use percentage error
		while (eps <= fabs(result - curr_sum) / result) {
			curr_sum = result;
			h = h / 2.0;
			result = simpson_rule(a, b, h, n1);
		}
	}
	else {
		result = simpson_rule(a, b, h, n1, n2);
		// use percentage error
		while (eps <= fabs(result - curr_sum) / result) {
			curr_sum = result;
			h = h / 2.0;
			result = simpson_rule(a, b, h, n1, n2);
		}
	}
	return result;
}


void prepare_matrix(std::vector<std::vector<double>> &matrix, int n, double a, double b, double eps) {
	int columns = n + 2;
	matrix.resize(n + 1);
	for (int i = 0; i <= n; ++i) {
		matrix[i].resize(columns);
		for (int j = 0; j <= n; ++j)
			matrix[i][j] = integrate(a, b, eps, j, i);

		matrix[i][n + 1] = integrate(a, b, eps, i);
	}
}



std::vector<double> gauss_method(std::vector<std::vector<double>> &matrix) {
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


double power(double x, int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;

	double res = 1;
	for (auto i = 0; i < n; ++i)
		res *= x;
	return res;
}


double calc_polynomial(std::vector<double> vect, double x) {
	int size = vect.size();
	double Px = 0;
	for (auto i = 0; i < size; ++i)
		Px += vect[i] * chebyshev(x, i);
	return Px;
}


double std_dev(double a, double b, std::vector<double> alpha, double eps) {
	double x = a;
	double item;
	double result = 0;
	double h = sqrt(eps);
	int n = (int)((b - a) / h);
	h = (b - a) / n;

	for (auto i = 0; i < n; ++i) {
		item = f(x) - calc_polynomial(alpha, x);
		result += item * item;
		x += h;
	}
	return sqrt(result/(n + 1));
}


void print_res(double a, double b, std::vector<double> alpha, double eps, FILE *f1, FILE *f2) {
	double x = a;
	double item;
	double h = sqrt(eps);
	int n = (int)((b - a) / h);
	h = (b - a) / n;
	for (auto i = 0; i < n; ++i) {
		item = calc_polynomial(alpha, x);
		fprintf(f1, "%.3g\n", x);
		fprintf(f2, "%.3g\n", item);
		x += h;
	}
}





