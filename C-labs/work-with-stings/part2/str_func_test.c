#include "str_func.h"
int main() {
	char *test_string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz;
	int argz_len;
	char *str = "SHELL=/bin/bash";
	
	argz_create_sep(test_string, 58, &argz, &argz_len);
	argz_print(argz, argz_len);
	printf("%d\n",argz_count(argz, argz_len));
	printf("\n");

	argz_add(&argz, &argz_len, str);
	argz_print(argz, argz_len);
	printf("%d\n", argz_count(argz, argz_len));
	printf("\n");

	argz_delete(&argz, &argz_len, "usr=monty");
	argz_print(argz, argz_len);
	printf("%d\n", argz_count(argz, argz_len));
	printf("%d\n", argz_len);
	printf("\n");

	argz_insert(&argz, &argz_len, "usr=monty", "LANG=en_US.UTF-8");
	argz_print(argz, argz_len);
	printf("\n");

	printf("%s\n", argz_next(argz, argz_len, "LANG=en_US.UTF-8"));
	printf("\n");

	argz_replace(&argz, &argz_len, "usr=monty", "Hasla");
	argz_print(argz, argz_len);
	return 0;
}