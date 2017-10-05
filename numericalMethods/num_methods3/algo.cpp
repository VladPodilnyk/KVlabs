#include "algo.h"

element search_el(std::vector<std::vector<double>> &matrix) {
	element result;
	int i, j;
	int size = matrix.size();
	result.item = matrix[0][0];
	result.row = 0;
	result.column = 0;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
			if (fabs(matrix[i][j]) > fabs(result.item)) {
				result.item = matrix[i][j];
				result.row = i;
				result.column = j;
			}
	return result;
}



std::vector<std::vector<double>> create_extended_matrix(std::vector<std::vector<double>> &matrix, std::vector<double> &free_mem){
	int size = matrix.size();
	int new_size = size + 1;
	int i;
	std::vector<std::vector<double>> matrix_exd(size);

	for (i = 0; i < size; ++i) {
		matrix_exd[i] = matrix[i];
		matrix_exd[i].resize(new_size);
		matrix_exd[i][size] = free_mem[i];
	}

	return matrix_exd;
}



void reset(std::vector<std::vector<double>> &matrix, int row, int column) {
	int i, j;
	int size = matrix.size();
	int c_size = size + 1;
	for (i = 0; i < size; ++i)
		matrix[i][column] = 0;
	for (j = 0; j < c_size; ++j) {
		if (j == column)
			continue;
		matrix[row][j] = 0;
	}
}

  
std::vector<double> m_vect_calculate(std::vector<std::vector<double>> &matrix, element value){
	int size = matrix.size();
	std::vector<double> m_vector(size - 1); 
	int i, j = 0;
	for (i = 0; i < size; ++i) {
		if (i == value.row)
			continue;

		m_vector[j] = -matrix[i][value.column] / value.item;
		++j;
	}
	return m_vector;
}


void transf(std::vector<std::vector<double>> &matrix, std::vector<double> m_vect, int main_row_indx) {
	int size = matrix.size();
	std::vector<double> tmp(size);
	int i, j = 0;

	tmp = matrix[main_row_indx];

	for (i = 0; i < size; ++i) {
		if (i == main_row_indx)
			continue;

		std::transform(matrix[main_row_indx].begin(), matrix[main_row_indx].end(), matrix[main_row_indx].begin(), 
					    std::bind1st(std::multiplies<double>(), m_vect[j]));

		std::transform(matrix[i].begin(), matrix[i].end(), matrix[main_row_indx].begin(), matrix[i].begin(), std::plus<double>());

		matrix[main_row_indx] = tmp;
		++j;
	}
}




std::vector<root> select(std::vector<std::vector<double>> &matrix, std::vector<double> &free_mem) {
	int i, new_root_indx, k = 0;
	int counter = 0;
	int size = matrix.size();
	int new_size = size + 1;
	double sum = 0;
	std::vector<double> tmp(size);
	std::vector<double> substruct_vect(size);
	std::vector<double> result;
	std::vector<root> res(size);
	std::vector<std::vector<double>> root_matrix(size);
	std::vector<std::vector<double>> matrix_m = create_extended_matrix(matrix, free_mem);
	std::vector<double> m_vector(size - 1);
	std::unordered_map<int, bool> vect;
	element current_max_element;

	//creating matrix with roots for equtation 

	while (counter < size) {
		current_max_element = search_el(matrix_m);
		if (!current_max_element.item)
			return res;

		m_vector = m_vect_calculate(matrix_m, current_max_element);
		transf(matrix_m, m_vector, current_max_element.row);
		root_matrix[counter] = matrix_m[current_max_element.row];
		reset(matrix_m, current_max_element.row, current_max_element.column);
		++counter;
	}

	for (i = 0; i < size; ++i)
		vect.insert({i, false});

	//searching for root

	counter -= 2;
	//int l = root_matrix[current_max_element.row][size];
	res[0].value = root_matrix[size - 1][size] / current_max_element.item;
	res[0].var_number = current_max_element.column;
	new_root_indx = 1;
	vect[res[0].var_number] = true;
	while (counter >= 0) {
		int k = res.size();
		for (i = 0; i < new_root_indx; ++i) {
			double l = root_matrix[counter][res[i].var_number];
			double h = res[i].value;
			sum += root_matrix[counter][res[i].var_number] * res[i].value;
		}

		for (i = 0; i < size; ++i)
			if (vect[i] == false && root_matrix[counter][i] != 0) {
				k = i;
				break;
			}

		res[new_root_indx].value = (root_matrix[counter][size] - sum) / root_matrix[counter][k];
		res[new_root_indx].var_number = k;
		sum = 0;
		++new_root_indx;
		vect[k] = true;
		--counter;
	}

	return res;
}


// algorithm for second task of the lab

std::vector<double> iter(std::vector<std::vector<double>> &a_matrix, std::vector<double> &b_column, double eps) {
	std::vector<double> tmp, copy;
	std::vector<double> aproximation_vect = b_column;
	int i, j, k;
	int size = a_matrix.size();
	double q, norm, current_sum = 0;

	q = 0;
	for (i = 0; i < size; ++i) {
		std::for_each(a_matrix[i].begin(), a_matrix[i].end(), [&](double n) {
			current_sum += fabs(n);
		});

		/*for (std::vector<double>::iterator it = a_matrix[i].begin(); it != a_matrix[i].end(); ++it)
			current_sum += fabs(*it);*/

		if (current_sum > q && current_sum < 1)
			q = current_sum;
		current_sum = 0;
	}

	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j)
			if (j != i)
				current_sum += a_matrix[i][j] * b_column[j];

		aproximation_vect[i] = b_column[i] + current_sum ;
		current_sum = 0;
	}

	k = 2;
	tmp = aproximation_vect;
	while (true) {
		for (i = 0; i < size; ++i) {
			for (j = 0; j < size; ++j)
				current_sum += a_matrix[i][j] * tmp[j];

			aproximation_vect[i] = b_column[i] + current_sum;
			current_sum = 0;
		}
		copy = aproximation_vect;
		std::transform(copy.begin(), copy.end(), tmp.begin(), copy.begin(), std::minus<double>());
		norm = fabs(copy[0]);
		for (i = 1; i < size; ++i)
			if (fabs(copy[i]) > norm)
				norm = fabs(copy[i]);

		double l = eps * (1 - q) / q;
			
		if (norm <= eps * (1 - q) / q)
			return aproximation_vect;
		//std::cout << k << " " << norm << std::endl ;
		tmp = aproximation_vect;
		++k;
	}
}