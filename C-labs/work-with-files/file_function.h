/**************************************************
*file: file_function.h
*synopsis: declarations for file functions
*author: podilnyk
*written: 08.12.2015
**************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF_SIZE  100
#pragma warning(disable: 4022)
#pragma warning(disable: 4133)
#pragma warning(disable: 4047)

typedef struct {
	char manufacturer[127];// manufacturer
	char model[128];// model name
	int year;	 // year of manufacture
	float price;// price
	int x_size;// the gorizontal size of the scan area
	int y_size;// the vertical size of the scan area
	int optr; // optical resolution
} SCAN_INFO;

typedef struct {
	int rec_nmb;//number of records
	SCAN_INFO *recs;//records 
}RECORD_SET;


// function prototypes
void wrt_bin_file(SCAN_INFO *rec,const char *name_f);
struct SCAN_INFO* get_rec(char *csv_line);
void init();
int make_index(char *dat, char *field_name);
RECORD_SET * get_recs_by_index(char *dat, char *indx_field);
void reindex(char *dat);
int del_scan(char *dat, int n);
void txt_out(FILE *dat_f, FILE *txt, int price);