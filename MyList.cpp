#pragma once
#include "stdafx.h"
#include "MyList.h"

template <class T>
MyList<T>::MyList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

template <class T>
MyList<T>::~MyList() {
	if(head != NULL) {
		removeList();
		head = NULL;
		tail = NULL;
	}
}



/*Sprawdza, czy element jest bli¿ej lewego czy prawego koñca listy a nastêpnie iteruje*/
template <class T>
typename MyList<T>::ListElement *MyList<T>::getElementAt(const unsigned int index) {
	MyList<T>::ListElement* element;
	if(index < size) {
		if(index > size / 2) {
			element = tail;
			for(unsigned int i = size - 1; i > index; i--) {
				element = element->previous;
			}
		} else {
			element = head;
			for(unsigned int i = 0; i < index; i++) {
				element = element->next;
			}
		}
		return element;
	} else {
		std::cerr<<"Bad index!"<<std::endl;
		return NULL;
	}
}
template <class T>
/* Osobne przypadki dla pierwszego elementu, koñca i pocz¹tku */
void MyList<T>::add(const unsigned int index, const T value) {
	if(index > size) {
		std::cerr<<"Bad index!"<<std::endl;
	} else {
		ListElement* newElement = new ListElement(value);
		if (index == size) {
			if(tail == NULL) {
				tail = newElement;
				head = newElement;
			} else {
				tail->next = newElement;
				newElement->previous = tail;
				tail = newElement;
			}
		} else if (index == 0) {
			head->previous = newElement;
			newElement->next = head;
			head = newElement;
		} else {
			ListElement* element = getElementAt(index);
			newElement->next = element;
			newElement->previous = element->previous;
			element->previous->next = newElement;
			element->previous = newElement;
		}
		size++;
	}
}
template <class T>
T MyList<T>::removeAt(const int index) {
	ListElement* element = getElementAt(index);
	return remove(element);
}

/* Osobne przypadki dla ostatniego elementu, koñca i pocz¹tku */
template <class T>
T MyList<T>::remove(ListElement* element) {
	int result = INT_MIN;
	if(element != NULL) {
		result = element->value;
		if(element == tail) {
			ListElement* oldElement = tail;
			if(head != tail) {
				tail = tail->previous;
				tail->next = NULL;
			} else {
				tail = NULL;
				head = NULL;
			}
			delete oldElement;
		} else if(element == head) {
			head = element->next;
			delete head->previous;
			head->previous = NULL;
		} else {
			element->previous->next = element->next;
			element->next->previous = element->previous;
			delete element;
		}
		size--;
	}
	return result;
}

template <class T>
int MyList<T>::findFirstOccurence(const T& value) {
	ListElement* element = head;
	for(unsigned int i = 0; i < size; i++) {
		if(element->value == value) {
			return i;
		}
		element = element->next;
	}
	return -1;
}
template <class T>
void MyList<T>::removeList(void) {
	ListElement* element = head;
	while(element != NULL) {
		ListElement* oldElement = element;
		element = element->next;
		delete oldElement;
	}
}
template <class T>
int MyList<T>::removeFirstOccurence(const T& value) {
	ListElement* element = head;
	for(unsigned int i = 0; i < size; i++) {
		if(element->value == value) {
			return i;
		}
		element = element->next;
	}
	std::cerr<<"Not found!"<<std::endl;
	return -1;
}