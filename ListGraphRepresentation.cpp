#pragma once
#include "stdafx.h"
#include "ListGraphRepresentation.h"

ListGraphRepresentation::ListGraphRepresentation(bool isDigraph, unsigned int vertexCount) 
	: GraphRepresentationInterface(isDigraph, vertexCount) {
	createLists();
}

void ListGraphRepresentation::clear() {
	removeLists();
	createLists();
}

void ListGraphRepresentation::removeLists() {
	for (int i = 0; i < vertexCount; i++) {
		delete edgesList[i];
	}
	delete edgesList;
	edgesList = NULL;
}

void ListGraphRepresentation::createLists() {
	edgesList = new EdgeList*[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
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
	}
	return exist;
}

unsigned ListGraphRepresentation::vertexDegree(unsigned vertex) {
	return edgesList[vertex]->getSize();
}

int ListGraphRepresentation::searchEdge(unsigned v, unsigned u) {
	return edgesList[v]->getWeight(u);
}