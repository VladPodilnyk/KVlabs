/***************************************************************
*file: string_methods.h
*synopsis: The string_methods functions search substring
*create palindrom
*recognaize palindrom.
* These functions are declared in the include file "string_methods.h".
*author: podilnyk
*related files: none
*written: 06.09.2015
****************************************************************/
#include "string_methods.h" 
/*The substr function searches an index of the first entry substring to string */
int substr(const char *string1, const char *string2) {
	char *first_occur = strstr(string1, string2);	//first occurrence
	if ((0 == strlen(string2)) || (NULL == first_occur))
		return -1;
	else {
		int len = strlen(string1);
		int len_sub = strlen(first_occur);
		return  len - len_sub;
	}
}

/*The subseq function returns the longest common number of characters of two strings. */
int subseq(const char *string1, const char *string2) {
	int j = 0, k = 0;
	int counter = 0, max_counter = 0;
	int i, lenght = strlen(string1), len = strlen(string2);
	for ( i = 0; i < lenght; i++) {
		while ((string1[i] != string2[j]) && (j < len - 1))
			j++;

		if (string1[i] == string2[j]) {
			counter++;
			j++;
			if (j > len)
				j = 0;
		}
		else {
			j = 0;
			counter = 0;
		}
		if (counter > max_counter)
			max_counter = counter;
	}
	return  max_counter;
}

// The ispal function returns 1, if word is palindrom else returns 0
char ispal(const char *string) {
	int index = 0, len = strlen(string);
	while (index < len / 2) {
		if (string[index] != string[len - index - 1]) {
			return 0;
		}
		index++;
	}
	return 1;

}

//The makepal function recives string and make palindrom
char* makepal(const char *str) {
	char *palindrome = NULL;
	int index;
	int k = 0, j = strlen(str); // k - store index of first occurent of palindrome
	int i;

	if (ispal(str))
		return str;     

	for ( i = 0; i <= j - 1; i++)
		if (str[i] != str[j-1]) k = i; 
		else j--;
	
	
	palindrome = (char*)malloc((j + k + 2) * sizeof(char)); // allocate memory for palindrome
	for (i = 0, index = k; i < j; i++, index--) {       // creating palindrome
		palindrome[i] = str[i];
		if (0 <= j)
			palindrome[j + i] = str[index];
	}
	palindrome[j + k + 1] = '\0';

	return palindrome;
}
//The txt2double function records numbers to dynamic massive
double* txt2double(const char *str, int *size) {
	int i, counter = 0, len = strlen(str);
	char *temp_str = NULL, *check_str = NULL;
	double *vector_of_double = NULL;
	*size = 0;
	for (i = 0; i < len; i++) {
		if (str[i] == ';')
			counter++;
	}
	*size = counter + 1;
	temp_str = (char*)malloc(sizeof(str)+1);
	vector_of_double = (double*)malloc((counter + 2)*sizeof(double));
	for (i = 0; i < len; i++) {
		if (str[i] == ';')
			temp_str[i] = '\0';
		else
			temp_str[i] = str[i];
	}
	temp_str[len] = '\0';
	i = 0;
	len = 0;
	check_str = temp_str;
	while (i < *size ) {
		if (0 == atof(check_str)) 
			if ('0' != check_str[0]) {
				*size = 0;
				break;
			}	

	    vector_of_double[i] = atof(check_str);
		check_str += strlen(check_str) + 1;
		i++;
	}
	return vector_of_double;
}	
