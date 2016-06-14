/*!
* file: main.cpp
* synopsis: Database class test
*/
#include "Database.h"

int main() {
	Database db;
	db.LoadFromFile("input.csv");
	//db.DisplayAll();

	db.ArrangeSubordinates();
	//db.DisplayAll(); 

	
	Employee *employee = new Employee("Matt", "Murdock", 26, 13);
	employee->SetDepartment("HK");
	employee->SetSalary(600);

	db.HireEmployee(employee);

	Manager* manager = new Manager("Frank", "Castle", 30, 55);
	manager->SetDepartment("HK");
	manager->SetSalary(2000);

	db.HireEmployee(manager);

	db.FireEmployee(0);

	db.DisplayAll(); 

	return 0;
}
