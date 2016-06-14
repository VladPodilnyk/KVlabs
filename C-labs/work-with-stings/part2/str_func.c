/***************************************************************
*file: str_func.h
*synopsis: The str_func functions makes argz vector, 
*returns number ofl elements in argz, conacats strings, etc.
* These functions are declared in the include file "str_func.h".
*author: podilnyk
*related files: none
*written: 11.10.2015
****************************************************************/
#include "str_func.h"
// argz_create_sep function makes a vector from null-terminated string
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {
	int i = 0, len = strlen(string);
	char *string_dublicate;
	*argz_len = len + 1;
	string_dublicate = (char*)malloc((len + 1)*sizeof(char));
	for (i; i < len; i++) {
		if (sep == (int)string[i])
			string_dublicate[i] = '\0';
		else
			string_dublicate[i] = string[i];
	}
	string_dublicate[len] = '\0';
	*argz = string_dublicate;
	return OK;
}
//argz_count function returns number of element in argz vector
size_t argz_count(const char *argz, size_t argz_len) {
	size_t counter = 0;
	int index = 0;
	char *check_string = NULL;
	check_string = argz;
	while (index < argz_len) {
		index += strlen(check_string) + 1;
		check_string += strlen(check_string) + 1;
		counter++;
	}
	return counter;
}

// argz_add function adds elemnt to argz vector and change argz_len
error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	int i = (int)*argz_len,
		j = 0,
		str_len = strlen(str);
	char *dublicate = (char*)realloc(*argz, (str_len + *argz_len) * sizeof(char));
	dublicate[*argz_len - 1] = '\0';
	for (j; j < str_len; j++) 
		dublicate[*argz_len + j] = str[j];

	dublicate[str_len + *argz_len] = '\0';
	*argz = dublicate;
	*argz_len += str_len + 1;
	return OK;
}

// argz_delete function delete entry from argz vector
void argz_delete(char **argz, size_t *argz_len, char *entry) {
	int i = 0, len = 0, index_l = 0, index_r = 0;
	char *dublicate = NULL, *argz_new = NULL;
	size_t num_of_elem = argz_count(*argz, *argz_len);
	dublicate = *argz;
	for (i; i < num_of_elem; i++ ) {
		if (strcmp(entry, dublicate) == 0 )
			break;
		index_l += strlen(dublicate) + 1;
		dublicate += strlen(dublicate) + 1;
	}
	len = strlen(dublicate);
	index_r += index_l + len + 1;
	*argz_len -= len + 1;
	argz_new = (char*)malloc((*argz_len) * sizeof(char));
	for (i = 0; i < index_l; i++) 
		argz_new[i] = (*argz)[i];
	
	for (index_r, i; i < *argz_len; index_r++, i++)             
		argz_new[i] = (*argz)[index_r];

	*argz = argz_new;
}

//argz_insert function insert entry to argz vector to point befor another element
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {
	int i = 0, j = 0, len = 0, index = 0;
	char *dublicate = NULL, *argz_new = NULL;
	size_t num_of_elem = argz_count(*argz, *argz_len);
	dublicate = *argz;
	for (i; i < num_of_elem; i++) {
		if (strcmp(before, dublicate) == 0)
			break;
		index += strlen(dublicate) + 1;
		dublicate += strlen(dublicate) + 1;
	}

	if (strcmp(before, dublicate) != 0)
		return BAD;

	len = strlen(entry);
	argz_new = (char*)malloc((*argz_len + len) * sizeof(char));
	for (i = 0; i < index; i++)
		argz_new[i] = (*argz)[i];
	for (i, j; j <= len; i++, j++)
		argz_new[i] = entry[j];
	for (i, index; index < *argz_len; i++, index++)
		argz_new[i] = (*argz)[index];

	*argz_len = *argz_len + strlen(entry);
	*argz = argz_new;
	return OK;
}

//argz_next function returns a pointert to the next element in argv vector 
char* argz_next(char *argz, size_t argz_len, const char *entry) {
	int i = 0, len = 0;
	char *next;
	next = argz;
	len = strlen(next);
	if ((entry == 0) || (entry == NULL))
		return argz;

	while (i < argz_len) {
		if ((strcmp(entry, next) == 0) && (i + strlen(next) + 1 < argz_len)) {
			next += strlen(next) + 1;
			return next;
	    }
		i += strlen(next) + 1;
		next += strlen(next) + 1;
	}
	return 0;
}

//argz_replace function replace the string str in argz with string with
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {
	int i = 0, j = 0, index = 0, len = 0;
	size_t 	num_of_elem = argz_count(*argz, *argz_len);
	char *pointer = NULL, *argz_new = NULL;
	len = strlen(with);
	pointer = *argz;
	for (i; i < num_of_elem; i++) {
		if (strcmp(str, pointer) == 0) 
			break;
		index += strlen(pointer) + 1;
		pointer += strlen(pointer) + 1;
	}

	if (strcmp(str, pointer) != 0)
		return BAD;

	*argz_len = (*argz_len) + len - strlen(str);
	argz_new = (char*)malloc((*argz_len) * sizeof(char));
	for (i = 0; i < index; i++)
		argz_new[i] = (*argz)[i];
	for (j, i; j <= len; j++, i++ )
		argz_new[i] = with[j];

	index += strlen(str) + 1;
	for (i, index; i < *argz_len; i++, index++)
		argz_new[i] = (*argz)[index];

	*argz = argz_new;
	return OK;
}

//argz_print function prints argz vector
void argz_print(const char *argz, size_t argz_len) {
	int i = 0;
	char *pointer = NULL;
	size_t num_of_elem = argz_count(argz, argz_len);
	pointer = argz;
	for (i; i < num_of_elem ; i++) {
		printf("%s\n", pointer);
		pointer += strlen(pointer) + 1;
	}
	printf("\n");
}

