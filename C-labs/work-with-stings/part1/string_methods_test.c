#include "string_methods.h"
int main() {
	char *string = "abba";
	char *substring = "cbbc";
	char *string_test = "0;11.23;5;1;45.6;78";
	double *test_array = NULL;
	int *size, i;
	int num = -1;
	size = &num;
	//printf("%s\n", "substr: ");
	//printf("%d\n", substr(string, substring));
	//printf("%s\n", "subseq: ");
	//printf(" %d\n", subseq(string, substring));
	//printf("%s\n", "ispal: ");
	//printf("%d\n", ispal(string));
	printf("%s\n", "makepal: ");
	printf("%s\n", makepal(string));
	/*test_array = txt2double(string_test, size);
	for (i = 0; i < *size; i++)
		printf("%g\n", test_array[i]);
	printf("%s\n", "txt2double: ");
	printf("%d\n", *size);  */     
	return 0;
}      