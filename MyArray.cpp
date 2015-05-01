#include "stdafx.h"
#include "MyArray.h"

MyArray::MyArray(void) {
	baseArray = NULL;
	size = 0;
}

MyArray::~MyArray(void) {
	if(baseArray != NULL) {
		delete[] baseArray;
		baseArray = NULL;
	}
}

void MyArray::add(const unsigned int index, const int value) {
	if(index <= size) {
		if(size == 0) {
			size++;
			baseArray = new int[1];
			baseArray[0] = value;
		} else {
			size++;
			int* newBaseArray = new int[size];
			memmove(newBaseArray, baseArray, index * sizeof(int));
			newBaseArray[index] = value;
			memmove(newBaseArray + index + 1, baseArray + index, (size - (index + 1)) * sizeof(int));
			delete[] baseArray;
			baseArray = newBaseArray;
		}
	} else {
		std::cerr<<"Bad index!"<<std::endl;
	}
}

void MyArray::removeAt(const unsigned int& index) {
	if(index < size) {
		size--;
		int* newBaseArray = new int[size];
		memmove(newBaseArray, baseArray, index * sizeof(int));
		memmove(newBaseArray + index, baseArray + index + 1, (size - index) * sizeof(int));
		delete[] baseArray;
		baseArray = newBaseArray;
	} else {
		std::cerr<<"Bad index!"<<std::endl;
	}
}

void MyArray::printStructure(void) const {
	if(size < 1) {
		std::cerr<<"Nothing to show"<<std::endl;
	} else {
		for(unsigned int i = 0; i < size; i++) {
			std::cout<<baseArray[i]<<" | ";
		}
	}
	std::cout<<std::endl;
}

int MyArray::findFirstOccurence(const int& value) {
	for(unsigned int i = 0; i < size; i++) {
		if(value == baseArray[i]) {
			return i;
		}
	}
	return -1; //nic nie wypisuje gdy¿ zwalnia to program
}