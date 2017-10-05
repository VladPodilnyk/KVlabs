#include "algo.h"


int main() {
	double a1 = -1.3, b1 = -1.8, a2 = 0, b2 = 0.5, eps = 0.01;
	result element, item;
	int i;
	int iter_count[5];
	int tangent_count[5];
	printf("Iteration method\n---------------------------------------------------------\n");
	
	while (eps >= epsLimit) {
		element = iter(a2, b2, eps);
		printf("%25.15g%25.15g\n", element.res, element.precision);
		eps *= 0.001;
	}
	

	printf("\n");
	eps = 0.01;
	i = 0;
	while (eps >= epsLimit) {
		element = iter(a1, b1, eps);
		iter_count[i] = element.counter;
		++i;
		printf("%25.15g%25.15g\n", element.res, element.precision);
		eps *= 0.001;
	}
	

	printf("Newton method\n---------------------------------------------------------\n");
	eps = 0.01;
	i = 0;
	while (eps >= epsLimit) {
		item = tangent(a1, b1, eps);
		tangent_count[i] = item.counter;
		++i;
		printf("%25.15g%25.15g\n", item.res, item.precision);
		eps *= 0.001;
	}

	printf("\n");
	eps = 0.01;
	while (eps >= epsLimit) {
		item = tangent(a2, b2, eps);
		printf("%25.15g%25.20g\n", item.res, item.precision);
		eps *= 0.001;
	}

	printf("Comparing\n---------------------------------------------------------\n");
	eps = 0.01;
	i = 0;
	while (eps >= epsLimit) {
		printf("%20.15g%10d%10d\n", eps, iter_count[i], tangent_count[i]);
		++i;
		eps *= 0.001;
	}


	return 0;
}