#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
#include <fstream>
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
		vertexList->addAtEnd(i);
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
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			vertexList->addAtEnd(i);
			vertexList->addAtEnd(j);
		}
	}
	for (int i = 0; i < edgesToGenerate; i++) {
		std::uniform_int_distribution<int> edgeDistr(0, vertexList->getSize() - 1);
		int pos = edgeDistr(generator);
		if (pos % 2 == 1) {
			pos--;
		}
		int v1 = vertexList->removeAt(pos);
		pos++;
		int v2 = vertexList->removeAt(pos);
		bool exist = insertEdge(v1, v2, weightDistr(generator));
		if (exist) {
			i--;
		}
	}
}

void GraphRepresentationInterface::printMatrixGraph() {
	using namespace std;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			cout << searchEdge(i,j) << "  ";
		}
		cout << endl;
	}
}

void GraphRepresentationInterface::printListGraph() {
	using namespace std;
	for (int i = 0; i < vertexCount; i++) {
		cout << i << ": ";
		for (int j = 0; j < vertexCount; j++) {
			int weight = searchEdge(i, j);
			if (weight >= 0) {
				cout << j << "(" << weight << "), ";
			}
		}
		cout << endl;
	}
}

void GraphRepresentationInterface::loadFromFile() {
	using namespace std;
	char patch[64];
	int tmp;
	cout << "sciezka: ";
	cin >> patch;
	fstream file(patch, std::ios_base::in);
	while (file >> tmp) {
		int u, weight, v = tmp;
		file >> u;
		file >> weight;
		insertEdge(v, u, weight);
	}
	file.close();
}