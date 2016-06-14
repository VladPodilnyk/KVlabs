/***************************************************
*file: string_methods.h
*synopsis: declarations for string functions
*author: podilnyk
*written: 06.09.2015
****************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <malloc.h>
#ifndef STRING_METHODS_H
#define STRING_METHODS_H
#pragma warning(disable: 4018)

/*function prototypes*/
substr(const char *string1, const char *string2);
subseq(const char *string1, const char *string2);
char ispal(const char *string);
char* makepal(const char *);
double* txt2double(const char *, int *size);
#endif 