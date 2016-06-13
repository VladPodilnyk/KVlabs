#include "file_function.h"

int main() {
	RECORD_SET *rec = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	int i = 0;
	FILE dat, txt;
	init();
	make_index("Scanners.dat", "manufacturer");
	rec = get_recs_by_index("Scanners.dat", "manufacturer.idx");
	reindex("Scanners.dat");
	del_scan("Scanners.dat", 0);
	txt_out(&dat, &txt, 1000);
	return 0;
}