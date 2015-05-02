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
			next = NULL;
		}
		EdgeNode(Edge e) {
			value = e;
			next = NULL;
		}
		~EdgeNode() {
		}
	};
	EdgeNode* head;
	int vertex;
	unsigned int size;
public:
	inline unsigned getSize() { return size; }
	Edge pop(unsigned);
	EdgeList() {}
	EdgeList(int);
	EdgeList(EdgeList*);
	~EdgeList();
	void removeList(void);
	void add(unsigned int, int);
	void add(Edge edge);
	bool exist(unsigned);
	bool remove(unsigned);
	Edge getVal(unsigned);
};