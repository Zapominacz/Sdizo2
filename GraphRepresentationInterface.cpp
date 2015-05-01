#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
#include "MyList.h"

GraphRepresentationInterface::GraphRepresentationInterface(bool isDigraph, unsigned int vCount) {
	isDiGraph = isDigraph;
	vertexCount = vCount;
	edgeCount = 0;
}

void GraphRepresentationInterface::generateGraph(const unsigned int vertexCount, 
	float density, const int weightFrom, const int weightTo) {
	clear();
	int edgesToGenerate = (int)(density * vertexCount * (vertexCount - 1)) / 2;
	int spanningEdge = vertexCount - 1;
	std::random_device rand_dev;
	std::uniform_int_distribution<int> weightDistr(weightFrom, weightTo);
	std::mt19937 generator(rand_dev());
	
	MyList* vertexList = new MyList();
	MyList* addedVertexList = new MyList();
	for (int i = 0; i < vertexCount; i++) {
		vertexList->addAtEnd(i+1);
	}
	std::uniform_int_distribution<int> distr(0, vertexList->getSize() - 1);
	addedVertexList->addAtBeginning(vertexList->removeAt(distr(generator)));

	if (edgesToGenerate >= spanningEdge) {
		for (int i = 0; i < spanningEdge; i++) {
			std::uniform_int_distribution<int> distr(0, vertexList->getSize() - 1);
			std::uniform_int_distribution<int> distr2(0, addedVertexList->getSize() - 1);
			int newVertex = vertexList->removeAt(distr(generator));
			int oldVertex = addedVertexList->getValueAt(distr2(generator));
			insertEdge(oldVertex, newVertex, weightDistr(generator));
			addedVertexList->addAtEnd(newVertex);
		}
		edgesToGenerate -= spanningEdge;
	}
	delete addedVertexList;
	delete vertexList;
	vertexList = new MyList();
	for (int i = 1; i <= vertexCount; i++) {
		for (int j = 1; j <= vertexCount; j++) {
			vertexList->addAtEnd(j);
			vertexList->addAtEnd(j);
		}
	}

}