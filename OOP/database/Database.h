/*!
* file: Database.h
* synopsis: Database class definition
*/
#pragma once
#include "Manager.h"
#include <vector>
#include <fstream>
#include <sstream>

class Database {

public:
	Database() {};
	~Database() {};
	bool LoadFromFile(const char *file);
	//arranges "flat" database after loading from the file
	void ArrangeSubordinates();
	void AddSubordinates(Manager*);
	//hire a new employee
	Person* HireEmployee(Person *p);
	void DisplayDepartmentEmployees(std::string _department);
	//fire the employee
	bool FireEmployee(int id);
	void DisplayAll();

private:
	std::vector<Person*> employees;
};
