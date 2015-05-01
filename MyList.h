#pragma once
#include "stdafx.h"

template<typename T>
class MyList {
private:
	struct ListElement {
		ListElement* next;
		ListElement* previous;
		T value;
		ListElement(T newValue) {
			value = newValue;
			previous = NULL;
			next = NULL;
		}
	};
	ListElement* head;
	ListElement* tail;
	unsigned int size;

	ListElement* getElementAt(const unsigned int);
	T remove(ListElement* element);
public:
	MyList();
	~MyList();

	
	void removeList(void);
	T removeAt(const int);
	void add(const unsigned int, const T);
	int removeFirstOccurence(const T&);
	int findFirstOccurence(const T&);
	void printStructure(void) const;
	inline T getValueAt(const unsigned int index) { return getElementAt(index)->value; }

	inline void addAtBeginning(const T value) { return add(0, value); }
	inline void addAtEnd(const T value) { return add(size, value); }
	inline T removeAtBeginning() { return removeAt(0); }
	inline T removeAtEnd() { return removeAt(size - 1); }
	inline unsigned int getSize(void) const { return size; }
};