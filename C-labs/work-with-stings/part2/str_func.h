/***************************************************
*file: str_func.h
*synopsis: declarations for string functions
*author: podilnyk
*written: 11.10.2015
****************************************************/
#ifndef STR_FUNC_H
#define STR_FUNC_H

#include <stdio.h>
#include <string.h>
#include <stddef.h> 
#include <stdlib.h>

typedef enum { OK, BAD } error_t;

/*function prototypes*/
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len);
size_t argz_count(const char *argz, size_t arg_len);
error_t argz_add(char **argz, size_t *argz_len, const char *str);
void argz_delete(char **argz, size_t *argz_len, char *entry);
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry);
char * argz_next(char *argz, size_t argz_len, const char *entry);
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with);
void argz_print(const char *argz, size_t argz_len);
#endif 