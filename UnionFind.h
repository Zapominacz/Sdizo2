#pragma once
#include "stdafx.h"
/** Klasa wykorzystywana w algorytmie Kruskala do sprawdzania w jakim poddrzewie jest dany wierzcho³ek*/
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