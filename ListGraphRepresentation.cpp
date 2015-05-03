#pragma once
#include "stdafx.h"
#include "ListGraphRepresentation.h"

ListGraphRepresentation::ListGraphRepresentation(bool isDigraph, unsigned int vertexCount) 
	: GraphRepresentationInterface(isDigraph, vertexCount) {
	createLists();
}

ListGraphRepresentation::~ListGraphRepresentation() {
	removeLists();
}


void ListGraphRepresentation::clear(unsigned vc) {
	removeLists();
	vertexCount = vc;
	createLists();
	edgeCount = 0;
}

void ListGraphRepresentation::removeLists() {
	for (unsigned i = 0; i < vertexCount; i++) {
		delete edgesList[i];
	}
	delete[] edgesList;
	edgesList = NULL;
}

void ListGraphRepresentation::createLists() {
	edgesList = new EdgeList*[vertexCount];
	for (unsigned i = 0; i < vertexCount; i++) {
		edgesList[i] = new EdgeList(i);
	}
}

bool ListGraphRepresentation::insertEdge(unsigned v, unsigned u, int weight) {
	bool exist = edgesList[v]->exist(u);
	if (!exist) {
		edgesList[v]->add(u, weight);
		if (!isDiGraph) {
			edgesList[u]->add(v, weight);
		}
		edgeCount++;
	}
	return exist;
}

bool ListGraphRepresentation::deleteEdge(unsigned v, unsigned u) {
	bool exist = edgesList[v]->exist(u);
	if (exist) {
		edgesList[v]->remove(u);
		if (!isDiGraph) {
			edgesList[u]->remove(v);
		}
		edgeCount--;
	}
	return exist;
}

unsigned ListGraphRepresentation::vertexDegree(unsigned vertex) {
	return edgesList[vertex]->getSize();
}

int ListGraphRepresentation::searchEdge(unsigned v, unsigned u) {
	Edge* e = edgesList[v]->getVal(u);
	if (e == NULL) {
		return -1;
	} else {
		return e->weight;
	}
}

EdgeStack* ListGraphRepresentation::getAdjFor(unsigned v) {
	EdgeStack *result = new EdgeStack();
	EdgeList *tmp = new EdgeList(edgesList[v]);
	int vSize = tmp->getSize();
	for (unsigned i = 0; i < vSize; i++) {
		Edge *e = tmp->pop(0);
		result->push(e);
	}
	delete tmp;
	return result;
}

EdgeList* ListGraphRepresentation::getSimpleAdjFor(unsigned v) {
	return new EdgeList(edgesList[v]);
}