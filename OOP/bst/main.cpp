#include "BinTree.h"



int main() {
	CBinTree db;
	db.load_from_file("input.csv");
	//db.print();
	db.train_info(90);
	db.station_info("Lviv");
	db.delete_route(90);
	db.train_info(90);
	db.print();
	return 0;
}