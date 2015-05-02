#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
#include "Edge.h"

class EdgeStack {
private:
	struct EdgeNode {
		Edge val;
		EdgeNode* next;
	};
	EdgeNode* top;
public:
	EdgeStack();
	~EdgeStack();
	void makeStack(GraphRepresentationInterface*);
	void makeStack(GraphRepresentationInterface*, unsigned);
	Edge pop();
};