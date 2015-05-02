#pragma once
#include "stdafx.h"
#include "EdgeStack.h"

EdgeStack::EdgeStack() {
	top = NULL;
}

void EdgeStack::makeStack(GraphRepresentationInterface* graph) {
	int vc = graph->getVertexCount();
	for (int i = 0; i < vc; i++) {
		for (int j = 0; j < vc; j++) {
			int weight = graph->searchEdge(i, j);
			if (weight > -1) {
				Edge tmp = Edge(i, j, weight);
				EdgeNode* currEdge = top;
				EdgeNode* prevEdge = NULL;
				while (currEdge != NULL) {
					Edge e = currEdge->val;
					if (e.weight < tmp.weight) {
						if (prevEdge == NULL) {
							EdgeNode *t2 = new EdgeNode();
							t2->val = tmp;
							t2->next = top;
							top = t2;
						}
						else {
							EdgeNode *t2 = new EdgeNode();
							t2->val = tmp;
							prevEdge->next = t2;
							t2->next = currEdge;
						}
					}
					prevEdge = currEdge;
					currEdge = currEdge->next;
				}
			}
		}
	}

}

void EdgeStack::makeStack(GraphRepresentationInterface* graph, unsigned v) {
	int vc = graph->getVertexCount();
	for (int j = 0; j < vc; j++) {
		int weight = graph->searchEdge(v, j);
		if (weight > -1) {
			Edge tmp = Edge(v, j, weight);
			EdgeNode* currEdge = top;
			EdgeNode* prevEdge = NULL;
			while (currEdge != NULL) {
				Edge e = currEdge->val;
				if (e.weight < tmp.weight) {
					if (prevEdge == NULL) {
						EdgeNode *t2 = new EdgeNode();
						t2->val = tmp;
						t2->next = top;
						top = t2;
					}
					else {
						EdgeNode *t2 = new EdgeNode();
						t2->val = tmp;
						prevEdge->next = t2;
						t2->next = currEdge;
					}
				}
				prevEdge = currEdge;
				currEdge = currEdge->next;
			}
		}
	}
}
EdgeStack::~EdgeStack() {
	while (top != NULL) {
		EdgeNode *t2 = top;
		top = top->next;
		delete t2;
	}
}
Edge EdgeStack::pop() {
	EdgeNode *t2 = top;
	top = top->next;
	Edge r = t2->val;
	delete t2;
	return r;
}