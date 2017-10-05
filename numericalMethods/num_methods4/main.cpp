#include "algo.h"

int main() {
	double I_n, I = (sin(2.0) - sin(54.0)) / 4 + 13;
	element I_2n;
	double M = 2;
	double h, a = 1, b = 27, eps = 0.01;
	double delta[5];

	int n, i, j = 0;

	while (eps > 1e-10) {	
		h = sqrt(12 * eps / ((b - a) * M));

		I_n = trapezium_method(a, b, h);
		delta[j] = fabs(I - I_n);
		printf("%7g%17.14g%18.14g%15.8g%20.8g\n", eps, I, I_n, h, delta[j]);
		++j;
		eps *= 0.01;
	}


	printf("----------------------------------------------------------------------------\n");
	printf("%5s%15s%15s%15s%20s\n", "eps", "I_real", "I", "h", "delta");
	printf("----------------------------------------------------------------------------\n");
	for (i = 0; i < j; ++i) {
		I_2n = trapezium_method_dc(a, b, delta[i]);
		printf("%7g%17.14g%18.14g%15.8g%15.8g\n", delta[i], I, I_2n.value, I_2n.h, I - I_2n.value);
	}

	return 0;
}