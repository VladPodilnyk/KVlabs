/*!
* file: Employee.h
* synopsis: Employee class declaration
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

// An abstract class
class Person {
public:
	Person() {};
	Person(std::string first_name, std::string last_name, int _age) : age(_age),
		f_name(first_name), l_name(last_name) {	}
	virtual void Display(bool) = 0;
protected:
	std::string f_name;//first name
	std::string l_name;//last name
	int age;
};

// Information about employees
class Employee : public Person {
public:
	Employee() {};
	Employee(std::string _f_name, std::string _l_name, int _age, int _id) :
		Person(_f_name, _l_name, _age), id(_id) {salary = 0;};
	Employee(const Employee &e);
	Employee& operator=(const Employee &e);
	void SetSalary(int s) { salary = s; }
	void SetDepartment(std::string dept) { department = dept; }
	void SetId(int n) { id = n; }
	int GetId() { return id; }
	std::string GetDepartment() { return department; }
	virtual void Display(bool);

protected:
	std::string department;
	int salary;
	int id;
};

