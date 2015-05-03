#include "stdafx.h"
#include "UnionFind.h"

UnionFind::UnionFind(unsigned vCount) {
	vertexCount = vCount;
	baseArray = new Subtree*[vCount];
	for (unsigned int i = 0; i < vertexCount; i++) {
		baseArray[i] = new Subtree(); //ka¿dy wierzcho³ek jest drzewem
		baseArray[i]->vertex = i;
		baseArray[i]->parent = NULL;
	}
}

UnionFind::~UnionFind() {
	for (int i = 0; i < vertexCount; i++) {
		delete baseArray[i];
	}
	delete[] baseArray;
}

unsigned UnionFind::findSubtree(unsigned v) {
	Subtree* currSubtree = baseArray[v];
	Subtree* prev = NULL;
	while (currSubtree != NULL) {
		prev = currSubtree; //Szukam rodzica podrzewa
		currSubtree = currSubtree->parent;
	}
	return prev->vertex;
}

bool UnionFind::isNotTheSameUnion(unsigned u, unsigned v) {
	return findSubtree(u) != findSubtree(v);
}

void UnionFind::merge(unsigned v, unsigned u) {
	if (v == u) {
		return;
	}
	unsigned subtree1 = findSubtree(v);
	unsigned subtree2 = findSubtree(u); //umieszczam jedno drzewo jako rodzica drugiego
	baseArray[subtree1]->parent = baseArray[subtree2];
}