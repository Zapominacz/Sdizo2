#include "stdafx.h"
#include "UnionFind.h"

UnionFind::UnionFind(unsigned vCount) {
	vertexCount = vCount;
	subtrees = vCount;
	
	head = new Subtree();
	head->index = 0;
	head->parent = NULL;
	head->rank = 0;
	Subtree *tmp = head;
	for (unsigned int i = 0; i < vertexCount; i++) {
		tmp->nextSubtree = new Subtree();
		tmp->nextSubtree->index = i;
		tmp->nextSubtree->rank = 0;
		tmp->nextSubtree->parent = NULL;
		tmp = tmp->nextSubtree;
	}
}


UnionFind::~UnionFind() {
	while (head != NULL) {
		Subtree *tmp = head;
		head = head->nextSubtree;
		delete tmp;
	}
}

unsigned UnionFind::findSubtree(unsigned elementId) {
	
	Subtree* currSubtree = getAt(elementId);
	Subtree* tmp = currSubtree;

	while (currSubtree->parent != NULL) {
		currSubtree = currSubtree->parent;
	}
	Subtree* root = currSubtree;
	currSubtree = tmp;
	while (currSubtree != root)
	{
		Subtree* next = currSubtree->parent;
		currSubtree->parent = root;
		currSubtree = next;
	}

	return root->index;
}

bool UnionFind::isNotTheSameUnion(unsigned u, unsigned v) {
	return findSubtree(u) != findSubtree(v);
}

void UnionFind::merge(unsigned s1, unsigned s2) {
	if (s1 == s2) {
		return;
	}

	Subtree* set1 = getAt(s1);
	Subtree* set2 = getAt(s2);

	// Determine which node representing a set has a higher rank. The node with the higher rank is
	// likely to have a bigger subtree so in order to better balance the tree representing the
	// union, the node with the higher rank is made the parent of the one with the lower rank and
	// not the other way around.
	if (set1->rank > set2->rank)
		set2->parent = set1;
	else if (set1->rank < set2->rank)
		set1->parent = set2;
	else // set1->rank == set2->rank
	{
		set2->parent = set1;
		++set1->rank; // update rank
	}

	// Since two sets have fused into one, there is now one less set so update the set count.
	--subtrees;
}

UnionFind::Subtree* UnionFind::getAt(unsigned index) {
	Subtree* currSubtree = head;
	for (unsigned int i = 0; i < index; i++) {
		if (currSubtree = NULL) {
			return NULL;
		}
		currSubtree = currSubtree->nextSubtree;
	}
	return currSubtree;
}