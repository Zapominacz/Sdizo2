#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
#include <fstream>
#include <iomanip>
#include "MyList.h"

GraphRepresentationInterface::GraphRepresentationInterface(bool isDigraph, unsigned int vCount) {
	isDiGraph = isDigraph;
	vertexCount = vCount;
	edgeCount = 0;
}

void GraphRepresentationInterface::generateGraph(const unsigned int vertexCount,
	float density, const int weightFrom, const int weightTo) {
	clear(vertexCount);
	int edgesToGenerate = (int)((density * vertexCount * (vertexCount - 1))/ 2);
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
	EdgeList *el = new EdgeList();
	int jdelim = vertexCount;
	for (int i = 0; i < vertexCount; i++) {
		if (!isDiGraph) {
			jdelim = i;
		}
		for (int j = 0; j < jdelim; j++) {
			el->add(Edge(i, j, weightDistr(generator)));
		}
	}
	for (int i = 0; i < edgesToGenerate; i++) {
		std::uniform_int_distribution<int> edgeDistr(0, el->getSize() - 1);
		int pos = edgeDistr(generator);
		Edge gen = el->pop(pos);
		bool exist = insertEdge(gen.v1, gen.v2, gen.weight);
		if (exist) {
			i--;
		}
	}
}

void GraphRepresentationInterface::printMatrixGraph() {
	using namespace std;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			cout << setw(3);
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
	int v;
	int vc;
	cout << "sciezka: ";
	cin >> patch;
	fstream file(patch, std::ios_base::in);
	int ec;
	
	file >> ec;
	file >> vc;
	clear(vc);
	while (file >> v) {
		int u, weight;
		file >> u;
		file >> weight;
		insertEdge(v, u, weight);
	}
	if (edgeCount != ec) {
		cerr << "Cos nie tak" << endl;
	}
	file.close();
}


EdgeStack* GraphRepresentationInterface::getAdjFor(unsigned v) {
	EdgeStack *result = new EdgeStack();
	result->makeStack(this, v);
	return result;
}