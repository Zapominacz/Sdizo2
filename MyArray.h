#pragma once
#include "stdafx.h"

class MyArray {
private:
	int* baseArray;
	unsigned int size;
public:
	inline void removeFirstOccurence(const int& value) { return removeAt(findFirstOccurence(value)); }
	inline void removeAtBeginning(void) { return removeAt(0); }
	inline void removeAtEnd(void) { return removeAt(size - 1); }
	inline int getSize(void) const { return size; }
	inline int& getElementAt(const unsigned int& index) { return baseArray[index]; }
	inline void addAtBeginning(const int value) { return add(0, value); }
	inline void addAtEnd(const int value) { return add(size, value); }

	MyArray(void);
	~MyArray(void);

	void add(const unsigned int, const int);
	void removeAt(const unsigned int&);
	int findFirstOccurence(const int&);
	void printStructure(void) const;
};