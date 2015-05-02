#pragma once
#include "stdafx.h"
#include "Edge.h"

class EdgeStack {
private:
	struct EdgeNode {
		Edge *val;
		EdgeNode* next;
		EdgeNode() {
			next = NULL;
			val = NULL;
		}

		~EdgeNode() {
			if (val != NULL) {
				delete val;
				val = NULL;
			}
		}
	};
	unsigned size;
	EdgeNode* top;
public:
	unsigned getSize() { return size; }
	EdgeStack();
	~EdgeStack();
	void push(Edge*);
	Edge* pop();
};