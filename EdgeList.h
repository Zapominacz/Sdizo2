#pragma once
#include "stdafx.h"
#include "Edge.h"

class EdgeList {
private:
	struct EdgeNode {
		Edge value;
		EdgeNode* next;
		EdgeNode(int vertex2, int weight) {
			value = Edge(-1, vertex2, weight);
		}
		~EdgeNode() {
		}
	};
	EdgeNode* head;
	int vertex;
	unsigned int size;
public:
	inline unsigned getSize() { return size; }
	EdgeList() {}
	EdgeList(int);
	EdgeList(EdgeList*);
	~EdgeList();
	void removeList(void);
	void add(unsigned int, int);
	bool exist(unsigned);
	bool remove(unsigned);
	Edge getVal(unsigned);
};