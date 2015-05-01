#include "stdafx.h"
#include "EdgeList.h"

EdgeList::EdgeList(int vertex) {
	this->vertex = vertex;
	head = NULL;
}

EdgeList::EdgeList(EdgeList* copy) {
	EdgeNode* tmp = copy->head;
	while (tmp != NULL) {
		add(tmp->value.v2, tmp->value.weight);
		tmp = tmp->next;
	}
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

Edge EdgeList::getVal(unsigned vertex) {
	EdgeNode *tmp = head;
	while (tmp != NULL) {
		if (tmp->value.v2 != vertex) {
			tmp = tmp->next;
		} else {
			return tmp->value;
			break;
		}
	}
	return Edge(0, 0, 0);
}

bool EdgeList::remove(unsigned vertex) {
	bool result = false;
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		if (tmp->value.v2 != vertex) {
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
		if (tmp->value.v2 != vertex) {
			tmp = tmp->next;
		} else {
			result = true;
			break;
		}
	}
	return result;
}