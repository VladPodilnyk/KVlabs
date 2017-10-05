#include "algo.h"

double func(double x) {
	return sin(x) * sin(x);
}


double trapezium_method(double a, double b, double &h) {
	double I = (func(a) + func(b)) / 2;
	int  n = (b - a) / h;
	h = (b - a) / n;
	//std::cout << n*h << std::endl;
	double x = a;
	int i;

	for (i = 1; i < n; ++i) {
		x += h;
		I += func(x);
	}
	
	return h * I;
}


element trapezium_method_dc(double a, double b, double eps) {
	double I_n;
	element I_2n;
	int n = (b - a) / sqrt(eps);

	I_2n.h = (b - a) / n;
	I_n = trapezium_method(a, b, I_2n.h);

	n *= 2;
	I_2n.h = I_2n.h / 2;
	I_2n.value = trapezium_method(a, b, I_2n.h);

	while (fabs(I_n - I_2n.value) > 3 * eps) {
		I_n = I_2n.value;
		n *= 2;
		I_2n.h = I_2n.h / 2;
		I_2n.value = trapezium_method(a, b, I_2n.h);
		//std::cout << "keke" << std::endl;
	}
	return I_2n;
}