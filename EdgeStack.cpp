#pragma once
#include "stdafx.h"
#include "EdgeStack.h"

EdgeStack::EdgeStack() {
	top = NULL;
}
/** Umieszczam wartoœæ na stosie tak, aby by³ nadal posortowany*/
void EdgeStack::push(Edge* edge) {
	if (edge->weight > -1) {
		EdgeNode* currEdge = top;
		EdgeNode* prevEdge = NULL;
		EdgeNode *tmp = new EdgeNode();
		tmp->val = edge;
		if (currEdge == NULL) {
			top = tmp;
			size++;
			return;
		}
		while (currEdge != NULL) {
			Edge *ce = currEdge->val;
			if (ce->weight > edge->weight) {
				if (prevEdge == NULL) {
					tmp->next = top;
					top = tmp;
				} else {
					prevEdge->next = tmp;
					tmp->next = currEdge;
				}
				size++;
				return;
			} else {
				prevEdge = currEdge;
				currEdge = currEdge->next;
			}
		}
		prevEdge->next = tmp;
		size++;
	}
}

EdgeStack::~EdgeStack() {
	while (top != NULL) {
		EdgeNode *t2 = top;
		top = top->next;
		delete t2;
	}
}
Edge* EdgeStack::pop() {
	EdgeNode *t2 = top;
	top = top->next;
	Edge *r = t2->val;
	t2->val = NULL;
	size--;
	delete t2;
	return r;
}