#pragma once
#include "stdafx.h"

class UnionFind {
public:
	UnionFind(unsigned);
	~UnionFind();
	unsigned findSubtree(unsigned);
	void merge(unsigned, unsigned);
	bool isNotTheSameUnion(unsigned, unsigned);
private:
	struct Subtree
	{
		int rank;
		int index;
		Subtree* parent;
		Subtree* nextSubtree;
	};

	unsigned vertexCount; // the number of elements currently in the UnionFind data structure.
	unsigned subtrees; // the number of sets currently in the UnionFind data structure.
	Subtree* head; // the list of nodes representing the elements
	Subtree* getAt(unsigned);
};