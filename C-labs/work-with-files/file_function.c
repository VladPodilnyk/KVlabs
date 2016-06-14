/**************************************************
*file: file_function.c
*synopsis: definition for a file functions
*author: podilnyk
*written: 08.12.2015
**************************************************/
#include "file_function.h"
//implementation of functions

// function writes data to bda-file
void wrt_bin_file(SCAN_INFO *rec, const char *name_f) {
	FILE *dat_f;
	SCAN_INFO *tmp_rec = (SCAN_INFO*)malloc(sizeof(SCAN_INFO));
	int num_of_rec = 1, counter = 0;
	if ((dat_f = fopen(name_f, "rb+")) == NULL) {
		dat_f = fopen(name_f, "wb");
		fwrite(&num_of_rec, sizeof(int), 1, dat_f);
		fwrite(rec, sizeof(SCAN_INFO), 1, dat_f);
		free(tmp_rec);
		fclose(dat_f);
		return;
	}
	fread(&num_of_rec, sizeof(int), 1, dat_f);
	if (num_of_rec != 0) {
		for (counter; counter < num_of_rec; counter++) {
			fread(tmp_rec, sizeof(SCAN_INFO), 1, dat_f);
			if (!strcmp(tmp_rec->manufacturer, rec->manufacturer) &&
				!strcmp(tmp_rec->model, rec->model) &&
				tmp_rec->price == rec->price && tmp_rec->x_size == rec->x_size &&
				tmp_rec->y_size == rec->y_size && tmp_rec->year == rec->year &&
				tmp_rec->optr == rec->optr) {
				free(tmp_rec);
				fclose(dat_f);
				return;
			}
		}
	}
	num_of_rec++;
	fseek(dat_f, 0, SEEK_END);
	fwrite(rec, sizeof(SCAN_INFO), 1,  dat_f);
	fseek(dat_f, 0, SEEK_SET);
	fwrite(&num_of_rec, sizeof(int), 1, dat_f);  
	free(tmp_rec);
	fclose(dat_f);
}

// function reads one record of scanners
struct SCAN_INFO* get_rec(char *csv_line) {
	SCAN_INFO *rec = (SCAN_INFO*)malloc(sizeof(SCAN_INFO));
	int i = 0, len, count = 7;
	len = strlen(csv_line);
	for (i; i < len; i++) {
		if (csv_line[i] == ';')
			csv_line[i] = '\0';
	}
	i = 0;
	for (i; i < count; i++) {
		switch (i) {
			case 0: strcpy(rec->manufacturer, csv_line);
				    break;
			case 1: strcpy(rec->model, csv_line);
					break;
			case 2: rec->year = atoi(csv_line);
					break;
			case 3: rec->price = (float)atof(csv_line);
					break;
			case 4: rec->x_size = atoi(csv_line);
					break;
			case 5: rec->y_size = atoi(csv_line);
					break;
			case 6: rec->optr = atoi(csv_line);
					break;
			default:
				break;
		}
		csv_line += strlen(csv_line) + 1;
	}
	return rec;
}
// initialization of binary file
void init() {
	FILE *csv_f;
	SCAN_INFO *rec;
	int count = 0, size_rec = sizeof(SCAN_INFO), size_int = sizeof(int);
	char *buf = (char*)malloc((MAX_BUF_SIZE)* sizeof(char));
	remove("Scanners.dat");
	if ((csv_f = fopen("Scanners.csv", "r")) == NULL)
		return;
	while (fgets(buf, MAX_BUF_SIZE, csv_f) && strlen(buf)) {
		*(buf + strlen(buf) - 1) = '\0';
		rec = get_rec(buf);
		wrt_bin_file(rec, "Scanners.dat");
	}
	fclose(csv_f);
}

typedef struct {
	int index;
	union FIELD_NAME {
		int i;
		float f;
		char str[128];
	}field_name;
} DATA;


//makes index file for current dat-file
int make_index(char *dat, char *field_name) {
	FILE *dat_f, *indx_f;
	int i = 0, j = 0, count = 0, idx_min = 0;
	DATA *min = (DATA*)malloc(sizeof(DATA));
	SCAN_INFO *rec = (DATA*)malloc(sizeof(SCAN_INFO));
	DATA *vector;
	char *string = (char*)malloc((strlen(field_name) + 5) * sizeof(char));
	dat_f = fopen(dat, "r");
	fread(&count, sizeof(int), 1, dat_f);
	vector = (DATA*)malloc(count * sizeof(DATA));
	for (i; i < count; i++) {
		fread(rec, sizeof(SCAN_INFO), 1, dat_f);
		if (!strcmp("manufacturer", field_name)) {
			strcpy(vector[i].field_name.str, rec->manufacturer);
			vector[i].index = i;
		}
		else if (!strcmp("model", field_name)) {
			strcpy(vector[i].field_name.str, rec->model);
			vector[i].index = i;
		}
		else if (!strcmp("year", field_name)) {
			vector[i].field_name.i = rec->year;
			vector[i].index = i;
		}
		else if (!strcmp("price", field_name)) {
			vector[i].field_name.f = rec->price;
			vector[i].index = i;
		}
		else if (!strcmp("x_size", field_name)) {
			vector[i].field_name.i = rec->x_size;
			vector[i].index = i;
		}
		else if (!strcmp("y_size", field_name)) {
			vector[i].field_name.i = rec->y_size;
			vector[i].index = i;
		}
		else if (!strcmp("optr", field_name)) {
			vector[i].field_name.i = rec->optr;
			vector[i].index = i;
		}

	}
	i = 0;
	//sorting
	for (i; i < count - 1; i++) {
		if (!strcmp("manufacturer",field_name) || !strcmp("model",field_name)) {
			strcpy(min->field_name.str, vector[i].field_name.str);
			min->index = vector[i].index;
		}
		else if (!strcmp("year", field_name) || !strcmp("optr", field_name) || !strcmp("x_size", field_name) ||
				 !strcmp("y_size", field_name)) {
			min->field_name.i = vector[i].field_name.i;
			min->index = vector[i].index;
		}
		else {
			min->field_name.f = vector[i].field_name.f;
			min->index = vector[i].index;
		}
		j = i + 1;
		idx_min = i;
		for (j; j < count; j++) {
			if (!strcmp("manufacturer", field_name) || !strcmp("model", field_name)) 
				if (strcmp(min->field_name.str, vector[j].field_name.str) >= 0) {
					strcpy(min->field_name.str, vector[j].field_name.str);
					min->index = vector[j].index;
					idx_min = j;
				}
			
			if (!strcmp("year", field_name) || !strcmp("optr", field_name) || !strcmp("x_size", field_name) ||
				!strcmp("y_size", field_name)) 
				if (min->field_name.i >= vector[j].field_name.i) {
					min->field_name.i = vector[j].field_name.i;
					min->index = vector[j].index;
					idx_min = j;
				}

			if (!strcmp("price", field_name))
				if (min->field_name.f >= vector[j].field_name.f) {
					min->field_name.f = vector[j].field_name.f;
					min->index = vector[j].index;
					idx_min = j;
				}
		}

		if (!strcmp("manufacturer", field_name) || !strcmp("model", field_name)) {
			strcpy(vector[idx_min].field_name.str, vector[i].field_name.str);
			strcpy(vector[i].field_name.str, min->field_name.str);
			vector[idx_min].index = vector[i].index;
			vector[i].index = min->index;
		}
		else if (!strcmp("year", field_name) || !strcmp("optr", field_name) || !strcmp("x_size", field_name) ||
				 !strcmp("y_size", field_name)) {
			vector[idx_min].field_name.i = vector[i].field_name.i;
			vector[i].field_name.i = min->field_name.i;
			vector[idx_min].index = vector[i].index;
			vector[i].index = min->index;
		}
		else {
			vector[idx_min].field_name.f = vector[i].field_name.f;
			vector[i].field_name.f = min->field_name.f;
			vector[idx_min].index = vector[i].index;
			vector[i].index = min->index;
		}
	}
	strcpy(string, field_name);
	strcat(string, ".idx");
	indx_f = fopen(string, "w");
	i = 0;
	for (i; i < count; i++)
		fwrite(&vector[i].index, sizeof(int), 1, indx_f);

	free(rec);
	free(min);
	fclose(indx_f);
	return 0;
}

//return set of records
RECORD_SET * get_recs_by_index(char *dat, char *indx_field) {
	FILE *dat_f, *idx_f;
	RECORD_SET *data = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	int i = 0, j, index = 0;
	dat_f = fopen(dat, "rb");
	idx_f = fopen(indx_field, "r");
	fread(&data->rec_nmb, sizeof(int), 1, dat_f);
	data->recs = (SCAN_INFO*)malloc(data->rec_nmb * sizeof(SCAN_INFO));
	for (i; i < data->rec_nmb; i++) {
		fread(&index, sizeof(int), 1, idx_f);
		j = 0;
		for (j; j <= index; j++) 
			fread(&data->recs[i], sizeof(SCAN_INFO), 1, dat_f);

		fseek(dat_f, sizeof(int), SEEK_SET);
	}

	fclose(dat_f);
	fclose(idx_f);
	return data;
}

// creates index files for all fields in SCAN_INFO
void reindex(char *dat) {
	make_index(dat, "manufacturer");
	make_index(dat, "model");
	make_index(dat, "year");
	make_index(dat, "price");
	make_index(dat, "x_size");
	make_index(dat, "y_size");
	make_index(dat, "optr");
}

//delete one record in binary file
int del_scan(char *dat, int n) {
	FILE *dat_f;
	SCAN_INFO *records;
	int number_of_records, i = 0, j = 0;
	dat_f = fopen(dat, "rb");
	fread(&number_of_records, sizeof(int), 1, dat_f);
	records = (SCAN_INFO*)malloc((number_of_records - 1) * sizeof(SCAN_INFO));
	while (i < number_of_records) {
		if (i != n) {
			fread(&records[j], sizeof(SCAN_INFO), 1, dat_f);
			j++;
		} 
		else 
			fread(&records[j], sizeof(SCAN_INFO), 1, dat_f);
		
		i++;
	}
  	fclose(dat_f);
	dat_f = fopen(dat, "wb");
	fwrite(&j, sizeof(int), 1, dat_f);
	i = 0;
	for (i; i < j; i++) 
		fwrite(&records[i], sizeof(SCAN_INFO), 1, dat_f);
	fclose(dat_f);
	reindex(dat);
	return 0;
}

void txt_out(FILE *dat_f, FILE *txt, int price) {
	int count = 0, i = 0;
	SCAN_INFO *records;
	if ((dat_f = fopen("Scanners.dat", "rb")) == NULL)
		return;
	remove("Scanners.txt");
	fread(&count, sizeof(int), 1, dat_f);
	records = (SCAN_INFO*)malloc(count * sizeof(SCAN_INFO));
	for (i; i < count; i++) 
		fread(&records[i], sizeof(SCAN_INFO), 1, dat_f);
	i = 0;
  	txt = fopen("Scanners.txt", "w");
	for (i; i < count; i++) 
		if (records[i].price <= price) {
			fprintf(txt, "%s;", records[i].manufacturer);
			fprintf(txt, "%s;", records[i].model);
			fprintf(txt, "%d;", records[i].year);
			fprintf(txt, "%g;", records[i].price);
			fprintf(txt, "%d;", records[i].x_size);
			fprintf(txt, "%d;", records[i].y_size);
			fprintf(txt, "%d;\n", records[i].optr);
		}
	fclose(txt);
	fclose(dat_f);
	return;
}