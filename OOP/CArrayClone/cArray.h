/*
* file: cArray.h
* cArray class declaration
* written: 25/02/2016
*/
#pragma once
#include <string.h>
#include <stdio.h>
#include <math.h>

class cArray{
//The minimum number of element slots to allocate if a size increase is necessary. 
#define GROWBY 10
public:
	// Constructor/Destructor 
	cArray(void) : size(0), count(0), buf(NULL) {}
	~cArray(void) { delete []buf; }

	// Attributes

	// Gets the number of elements in this array
	int GetSize() const;
	// Gets the number of elements wich are not free
	int GetCount() const;

	// Returns the largest valid index
	int GetUpperBound() const;
	// Determines whetherr the array is empty
	bool IsEmpty() const;
	// Established the size of an empty or existing array
	// allocate memory if necessary
	void SetSize(int NewSize);

	// Operations

	// Frees all unused memory above the current upper bound
	// This function has no effect on the upper bound of the array
	void FreeExtra();

	// Removes all the elements from this array
	void RemoveAll();

	// Element access

	// Return the value at a given index
	int GetAt(int) const;
	//Sets the value for a given index; array not allowed to grow
	void SetAt(int n, int indx);

	// Growing the array

	// Adds an element to the end of the array; grows the array if necessary
	void Add(int);
	// Appends another array to the array; grows the array if necessary
	void Append(cArray *);
	// Copies another array to the array; grows the array if necessary
	void Copy(cArray *);

	// Insert/Removal

	// Insrets an element at a specified index
	void InsertAt(int n, int indx);
	// Removes an element at a specified index
	void RemoveAt(int indx);

	// Operators

	// Sets or gets element at the specified index
	int& operator [](int);

private:
	int size;
	int count;
	int *buf;
};

