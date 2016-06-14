/*!
* file: Employee.cpps
* synopsis: Employee class implementation
*/

#include "Employee.h"

Employee::Employee(const Employee &e) {
	if (!e.f_name.empty()) {
		f_name = e.f_name;
		l_name = e.l_name;
		age = e.age;
		id = e.id;
	}
	if (!e.department.empty())
		department = e.department;
	if (salary)
		salary = e.salary;
}

 Employee& Employee::operator=(const Employee& e) {
	 if (!e.f_name.empty()) {
		 f_name = e.f_name;
		 l_name = e.l_name;
		 age = e.age;
		 id = e.id;
	 }
	 if (!e.department.empty())
		 department = e.department;
	 if (salary)
		 salary = e.salary;
	 return *this;
}

 void Employee::Display(bool flag) {
	 if (flag) 
		 std::cout << "\t\t";
	 std::cout << "Employment type: employee" << std::endl;
	 if (flag) 
		 std::cout << "\t\t";
	 std::cout << "id: " << id << std::endl;
	 if (flag)
		 std::cout << "\t\t";
	 std::cout << f_name << " " << l_name << " age: " << age << " salary: " << salary << std::endl;
	 if (flag)
		 std::cout << "\n";
	 if (!flag)
		 std::cout << "department: " << department << "\n\n";
 }

