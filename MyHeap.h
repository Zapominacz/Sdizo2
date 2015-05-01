#pragma once
#include "stdafx.h"
#include <cmath>
/*Kopiec typu max*/
class MyHeap {
private:
	int* baseArray;
	unsigned int size;
	int super_wazna_zmienna;
	int getParentIndex(int);
	inline int getLeftChildIndex(int index) { return 2*index+1; }
	inline int getRightChildIndex(int index) { return 2*index+2; }
	void fixHeapDown(const unsigned int&);
	void printElement(int index);
public:
	MyHeap(void);
	~MyHeap(void);

	inline unsigned int getSize(void) { return size; }
	void fixHeapUp(void);
	void addAll(int*, int);
	int pop(void);
	void removeFirstOccurence(const int&);
	void push(int value);
	int find(const int&);
	void heapSort(void);

	void printStructure();
};