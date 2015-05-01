#pragma once
#include "stdafx.h"
#include "MyHeap.h"


MyHeap::MyHeap(void) {
	baseArray = new int[0];
	size = 0;
}

MyHeap::~MyHeap(void) {
	if(baseArray != NULL) {
		delete[] baseArray;
		baseArray = NULL;
	}
}

int MyHeap::pop() {
	if(size > 0) {
		int result = baseArray[0];
		size--;
		baseArray[0] = baseArray[size];
		int* newBaseArray = new int[size];
		memmove(newBaseArray, baseArray, size * sizeof(int));
		delete[] baseArray;
		baseArray = newBaseArray;
		fixHeapDown(0);
		return result;
	} else {
		std::cerr<<"Empty heap"<<std::endl;
		return -1;
	}
}

void MyHeap::push(int value) {
	int* newBaseArray = new int[size + 1];
	memmove(newBaseArray, baseArray, size * sizeof(int));
	delete[] baseArray;
	baseArray = newBaseArray;
	int parentIndex = getParentIndex(size);
	int childIndex = size;
	size++;
	while(parentIndex != -1 && baseArray[parentIndex] > value) {
		baseArray[childIndex] = baseArray[parentIndex];
		childIndex = parentIndex;
		parentIndex = getParentIndex(parentIndex);
	}
	baseArray[childIndex] = value;
}

int MyHeap::find(const int& value) {
	int savedSize = size;
	while(size > 0) {
		int tmp = baseArray[0];
		if(tmp == value) {
			int result = savedSize - size;
			size = savedSize;
			fixHeapUp();
			return result;
		} else {
			size--;
			baseArray[0] = baseArray[size];
			baseArray[size] = tmp;
			fixHeapDown(0);
		}
	}
	return -1; //nie znaleziono, napis wyciêto z powodu wydajnoœci cout
}

void  MyHeap::removeFirstOccurence(const int& value) {
	int savedSize = size;
	while(size > 0) {
		int tmp = baseArray[0];
		if(tmp == value) {
			savedSize--;
			int* newBase = new int[savedSize];
			memmove(newBase, baseArray + 1, savedSize * sizeof(int));
			delete[] baseArray;
			baseArray = newBase;
			size = savedSize;
			fixHeapUp();
			return;
		} else {
			size--;
			baseArray[0] = baseArray[size];
			baseArray[size] = tmp;
			fixHeapDown(0);
		}
	}
}

int MyHeap::getParentIndex(int index) { 
	if(index > 0) {
		return (index - 1) / 2; 
	} else {
		return -1;
	}
}

void MyHeap::fixHeapDown(const unsigned int& index) {
	unsigned int leftChildIndex = getLeftChildIndex(index);
	unsigned int rightChildIndex = getRightChildIndex(index);
	unsigned int maxValueIndex = index;
	if(leftChildIndex < size && baseArray[maxValueIndex] > baseArray[leftChildIndex]) {
		maxValueIndex = leftChildIndex;
	}
	if(rightChildIndex < size && baseArray[maxValueIndex] > baseArray[rightChildIndex]) {
		maxValueIndex = rightChildIndex;
	}
	if(maxValueIndex != index) {
		int temp = baseArray[index];
		baseArray[index] = baseArray[maxValueIndex];
		baseArray[maxValueIndex] = temp;
		return fixHeapDown(maxValueIndex);
	}
}

void MyHeap::fixHeapUp(void) {
	for(int i = size / 2; i >= 0; i--) {
		fixHeapDown(i);
	}
}

void MyHeap::heapSort(void) {
	fixHeapUp();
	int savedSize = size;
	for(int i = 0; i < savedSize; i++) {
		size--;
		int highest = baseArray[0];
		baseArray[0] = baseArray[size];
		baseArray[size] = highest;
		fixHeapDown(0);
	}
	size = savedSize;
}

void  MyHeap::addAll(int* src, int howMany) {
	int* newBase = new int[size + howMany];
	memmove(newBase, baseArray, size * sizeof(int));
	memmove(newBase + size, src, howMany * sizeof(int));
	size += howMany;
	delete[] baseArray;
	baseArray = newBase;
	fixHeapUp();
}

void MyHeap::printStructure() {
	int index = 0;
	printElement(index);
}

void MyHeap::printElement(int index) {
	if (index >= size) return;
	printElement(getRightChildIndex(index));
	int tmp = index;
	while (tmp > 0) {
		tmp--;
		tmp /= 2;
		std::cout << '\t';
	}
	std::cout << baseArray[index] << std::endl;
	printElement(getLeftChildIndex(index));
}

