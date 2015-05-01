#pragma once
#include "stdafx.h"
#include "Edge.h"

class EdgeList {
private:
	struct EdgeNode {
		unsigned int vertex;
		int weight;
		EdgeNode* next;
		EdgeNode(int vertex, int weight) {
			this->vertex = vertex;
			this->weight = weight;
		}
	};
	EdgeNode* head;
	int vertex;
	unsigned int size;
public:
	inline unsigned getSize() { return size; }
	EdgeList() {}
	EdgeList(int);
	~EdgeList();
	void removeList(void);
	void add(unsigned int, int);
	bool exist(unsigned);
	bool remove(unsigned);
	int getWeight(unsigned);
};