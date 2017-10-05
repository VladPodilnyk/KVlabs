#include "algo.h"

double phi(double x, double lambda) { return x - lambda * (-x*x - 2 * sin(x) + 1); }

double func(double x, char choice) { 
	switch (choice) {
		case 0: return x * x + 2 * sin(x) - 1;
		case 1: return 2 * (x + cos(x));
		case 2: return 2 * (1 - sin(x));
	} 
	//return 0;
}

result iter(double a, double b, double eps) {
	result iter_res;
	double xk, x0 = (b + a) / 2;
	double m1 = -2 * (a + cos(a)), M1 = -2 * (b + cos(b)), q, lambda;
 	lambda = 1 / M1;
	q = 1 - m1 / M1;
	xk = phi(x0, lambda);
	iter_res.counter = 0;
	while (fabs(xk - x0) > (1 - q) / q *eps) {
		x0 = xk;
		xk = phi(x0, lambda);
		++iter_res.counter;
	}

	iter_res.res = xk;
	iter_res.precision = fabs(xk - x0) * q / (1 - q);
	return iter_res;
}


result tangent(double a, double b, double eps) { 
	result rslt;
	rslt.res = func(b, 2) * func(b, 0) > 0 ? b : a;
	double da = fabs(func(a, 1));
	double db = fabs(func(b, 1));
	double m1 = da > db ? db : da;
	rslt.counter = 0;
	while (fabs(func(rslt.res, 0) / m1) > eps) {
		rslt.res = rslt.res - func(rslt.res, 0) / func(rslt.res, 1);
		++rslt.counter;
	}

	rslt.precision = fabs(func(rslt.res, 0) / m1);
	return rslt;
}