#include "helpers.h"


int main() {

	std::vector<std::vector<double>> matrix;
	std::vector<double> alpha;
	FILE *f1 = fopen("x.txt", "w");
	FILE *f2 = fopen("y.txt", "w");;
	double exit_state = 0.01;
	
	double standart_dev = 1;
	int polynomial_order = 5;
	printf("Order   Standart deviation\n");
	while (standart_dev > exit_state) {
		prepare_matrix(matrix, polynomial_order, a, b, eps);
		alpha = gauss_method(matrix);
		standart_dev = std_dev(a, b, alpha, eps);
		printf("%2i%10.4g\n", polynomial_order, standart_dev);
		++polynomial_order;
	}

	print_res(a, b, alpha, eps, f1, f2);
	fclose(f2);
	fclose(f1);
	return 0;

}