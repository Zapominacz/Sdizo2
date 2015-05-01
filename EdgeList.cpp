#include "stdafx.h"
#include "EdgeList.h"

EdgeList::EdgeList(int vertex) {
	this->vertex = vertex;
	head = NULL;
}

EdgeList::~EdgeList() {
	removeList();
	head = NULL;
}

void EdgeList::removeList() {
	while (head != NULL) {
		EdgeNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

void EdgeList::add(unsigned int vertex, int weight) {
	EdgeNode *newNode = new EdgeNode(vertex, weight);
	EdgeNode *next = head;
	EdgeNode *prev = NULL;
	while (next != NULL) {
		next->next;
	}
	if (prev == NULL) {
		head = newNode;
	} else {
		prev->next = newNode;
	}
	size++;
}