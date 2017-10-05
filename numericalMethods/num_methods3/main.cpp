#include "algo.h"

int main() {
	std::vector<std::vector<double>> matrix(size);
	std::vector<std::vector<double>> a_matrix(size);
	std::vector<double> free_mem  = {149, 257, 143, 144};
	std::vector<double> b_column = {-0.56 , 7.84, -0.05, 10.8};
	std::vector<double> result;
	int vsize;
	std::vector<root> res;
	for (int i = 0; i < size; ++i) {
		matrix[i].resize(size);
		a_matrix[i].resize(size);
	}
	matrix[0] = { 3, 19, 11, 8 };
	matrix[1] = { 9, 31, 3, 18 };
	matrix[2] = { 11, 7, 32, 13 };
	matrix[3] = { 12, 19, 12, 5 };
	
	a_matrix[0] = { 0, 0, -0.11, 0.33 };
	a_matrix[1] = { -0.158, 0, -0.579, -0.42 };
	a_matrix[2] = { 0.05, 0.6, 0, -0.4 };
	a_matrix[3] = { -0.6, -1.2, 0.8, 0};


	res = select(matrix, free_mem);
	result = iter(a_matrix, b_column, 1e-4);
	vsize = res.size();
	std::cout << "Select method\n\n";
	for (int i = 0; i < vsize; ++i)
		std::cout << res[i].value << " "<< res[i].var_number + 1 <<std::endl;

	std::cout << "\nSimple iteration method\n\n";

	vsize = result.size();
	for (int i = 0; i <	vsize; ++i)
		std::cout << std::setw(10) << result[i] << std::setw(5) << i + 1 << std::endl;

	return 0;
}