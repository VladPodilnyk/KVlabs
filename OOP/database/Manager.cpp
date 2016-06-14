/*!
* file: Manager.cpp
* synopsis: Manager class implementation
*/
#include "Manager.h"

Manager::Manager(const Manager& m) {
	if (!m.f_name.empty()) {
		f_name = m.f_name;
		l_name = m.l_name;
		age = m.age;
		id = m.id;
	}
	if (!m.department.empty())
		department = m.department;
	if (salary)
		salary = m.salary;
}

Manager& Manager::operator=(const Manager &m) {
	if (!m.f_name.empty()) {
		f_name = m.f_name;
		l_name = m.l_name;
		age = m.age;
		id = m.id;
	}
	if (!m.department.empty())
		department = m.department;
	if (salary)
		salary = m.salary;
	return *this;
}


void Manager::Display(bool) {
	std::cout << "Employment type: manager" << std::endl;
	std::cout << "id: " << id << std::endl;
	std::cout << f_name << " " << l_name << " age: " << age << " salary: " << salary << std::endl;
	std::cout << "department: " << department << std::endl;
	std::cout << "Subordinates: \n";
	DisplaySubordinates();
}

//add an employee to the subordinates list
Person* Manager::AddSubordinate(Person *p) {
	std::list<Person*>::iterator it = subordinates.begin();
	for (it; it != subordinates.end(); ++it)
		if (dynamic_cast<Employee*>(*it)->GetId() == dynamic_cast<Employee*>(p)->GetId())
			return NULL;
	subordinates.push_back(p);
	return *(subordinates.begin());
}

void Manager::DisplaySubordinates() {
	std::list<Person *>::iterator  it = subordinates.begin();
	if (subordinates.empty()) {
		std::cout << "\t\tNone\n\n";
		return;
	}
	for (it; it != subordinates.end(); it++)
		(*it)->Display(1);
		
}

void Manager::FireSubordinates(int id) {
	std::list<Person*>::iterator it = subordinates.begin();
	for (it; it != subordinates.end(); ++it)
		if (id == dynamic_cast<Employee*>(*it)->GetId()) {
			subordinates.remove(*it);
			return;
		}
}