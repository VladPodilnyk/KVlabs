/*!
* file: Database.cpp
* synopsis: Database class implementation
*/

#include "Database.h"
bool Database::LoadFromFile(const char *file) {
	std::ifstream flow(file);
	std::string item, type;
	std::vector<std::string> data;
	Employee *new_employee;
	Manager *new_manager;
	int counter;
	if (flow.is_open()) {
		while (std::getline(flow, type, ';')) {
			data.push_back(type);
			for (counter = 0; counter < 5; counter++) {
				std::getline(flow, item, ';');
				data.push_back(item);
			}
			std::getline(flow, item);
			data.push_back(item);
			if ("0" == data[0]) {
				new_employee = new Employee(data[2], data[3], stoi(data[4]), stoi(data[1]));
				new_employee->SetDepartment(data[5]);
				new_employee->SetSalary(stoi(data[6]));
				employees.push_back(new_employee);
				data.clear();
			}
			else
				if ("1" == data[0]) {
					new_manager = new Manager(data[2], data[3], stoi(data[4]), stoi(data[1]));
					new_manager->SetDepartment(data[5]);
					new_manager->SetSalary(stoi(data[6]));
					employees.push_back(new_manager);
					data.clear();
				}
		}
		flow.close();
		return 1;
	}
	flow.close();
	return 0;
}

void Database::AddSubordinates(Manager* manager) {
	std::vector<Person*>::iterator it = employees.begin();
	for (it; it != employees.end(); ++it)
		if (typeid(**it) == typeid(Employee) && dynamic_cast<Employee*>(*it)->GetDepartment() == manager->GetDepartment())
			manager->AddSubordinate(*it);
}

void Database::ArrangeSubordinates() {
	std::vector<Person*>::iterator it = employees.begin();
	for (it; it != employees.end(); ++it)
		if (typeid(**it) == typeid(Manager))
			AddSubordinates(dynamic_cast<Manager*>(*it));

}

Person* Database::HireEmployee(Person* p) {
	std::vector<Person*>::iterator it = employees.begin();
	for (it; it != employees.end(); ++it) {
		if (dynamic_cast<Employee*>(p)->GetId() == dynamic_cast<Employee*>(*it)->GetId())
			return NULL;
		if (typeid(*p) == typeid(Manager) && typeid(**it) == typeid(Manager) &&
			dynamic_cast<Employee*>(p)->GetDepartment() == dynamic_cast<Employee*>(*it)->GetDepartment())
			return NULL;
	}
	employees.push_back(p);
	ArrangeSubordinates();
	return p;
}

bool Database::FireEmployee(int id) {
	std::vector<Person*>::iterator it = employees.begin(), _it;
	bool flag = 0;
	for (it; it != employees.end(); ++it) {
		if (typeid(**it) == typeid(Manager))
			if (id == dynamic_cast<Employee*>(*it)->GetId()) {
				_it = it;
				flag = 1;
			}
			else
				dynamic_cast<Manager*>(*it)->FireSubordinates(id);
		else
			if (id == dynamic_cast<Employee*>(*it)->GetId()) {
				_it = it;
				flag = 1;
			}
	}
	if (flag)
		employees.erase(_it);
	return flag;
}

void Database::DisplayDepartmentEmployees(std::string _department) {
	std::vector<Person*>::iterator it = employees.begin();
	for (it; it != employees.end(); ++it)
		if (_department == dynamic_cast<Employee*>(*it)->GetDepartment())
			(*it)->Display(0);

	
}

void Database::DisplayAll() {
	std::vector<Person*>::iterator it = employees.begin();
	for (it; it != employees.end(); ++it)
		(*it)->Display(0);
}