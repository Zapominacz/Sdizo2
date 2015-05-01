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
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		tmp = tmp->next;
	}
	if (prev == NULL) {
		head = newNode;
	} else {
		prev->next = newNode;
	}
	size++;
}

int EdgeList::getWeight(unsigned vertex) {
	int result = -1;
	EdgeNode *tmp = head;
	while (tmp != NULL) {
		if (tmp->vertex != vertex) {
			tmp = tmp->next;
		} else {
			result = tmp->weight;
			break;
		}
	}
	return result;
}

bool EdgeList::remove(unsigned vertex) {
	bool result = false;
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		if (tmp->vertex != vertex) {
			tmp = tmp->next;
			prev = tmp;
		} else {
			result = true;
			if (prev == NULL) {
				head = tmp->next;
			} else {
				prev->next = tmp->next;
			}
			delete tmp;
			break;
		}
	}
	return result;
}

bool EdgeList::exist(unsigned vertex) {
	bool result = false;
	EdgeNode *tmp = head;
	while (tmp != NULL) {
		if (tmp->vertex != vertex) {
			tmp = tmp->next;
		} else {
			result = true;
			break;
		}
	}
	return result;
}