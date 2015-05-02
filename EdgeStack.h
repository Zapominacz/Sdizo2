#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"

class EdgeStack {
public:
	EdgeStack(GraphRepresentationInterface* graph) {
		int vc = graph->getVertexCount();
		for (int i = 0; i < vc; i++) {
			for (int j = 0; i < vc; i++) {
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
							} else {
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
	~EdgeStack() {
		while (top != NULL) {
			EdgeNode *t2 = top;
			top = top->next;
			delete t2;
		}
	}
	Edge pop() {
		EdgeNode *t2 = top;
		top = top->next;
		Edge r = t2->val;
		delete t2;
		return r;
	}
private:
	struct EdgeNode {
		Edge val;
		EdgeNode* next;
	};
	EdgeNode* top;
};