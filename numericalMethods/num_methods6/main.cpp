#include "spline.h"

int main() {
	int N = 100;
	FILE *f1 = fopen("x.txt", "w");
	FILE *f2 = fopen("y.txt", "w");;
	plot_spline(a, b, N, f1, f2);
	fclose(f2);
	fclose(f1);
	return 0;
}