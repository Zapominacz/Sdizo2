#pragma once
#include "stdafx.h"
#include <cmath>
/*Kopiec typu min*/
class MyHeap {
private:
	int* baseArray;
	int* valueArray;
	unsigned int size;
	int getParentIndex(int);
	inline int getLeftChildIndex(int index) { return 2*index+1; }
	inline int getRightChildIndex(int index) { return 2*index+2; }
	void fixHeapDown(const unsigned int&);
public:
	MyHeap(void);
	~MyHeap(void);
	int seekKey() { return baseArray[0]; }
	inline unsigned int getSize(void) { return size; }
	void fixHeapUp(void);
	int pop(void);
	void push(int key, int value);
	int getKey(const int&);
	void setKey(int, int);
};