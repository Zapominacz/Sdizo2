#pragma once
#include "stdafx.h"

class UnionFind {
private:
	struct Subtree {
		int vertex;
		Subtree* parent;
		Subtree* nextSubtree;
	};
	unsigned vertexCount;
	unsigned subtrees;
	Subtree** baseArray;
public:
	UnionFind(unsigned);
	~UnionFind();
	unsigned findSubtree(unsigned);
	void merge(unsigned, unsigned);
	bool isNotTheSameUnion(unsigned, unsigned);
};