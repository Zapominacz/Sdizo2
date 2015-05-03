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
/** generuje graf*/
void GraphRepresentationInterface::generateGraph(const unsigned int vertexCount,
	float density, const int weightFrom, const int weightTo) {
	clear(vertexCount);
	int edgesToGenerate = (int)((density * vertexCount * (vertexCount - 1))/ 2);
	if (isDiGraph) {
		edgesToGenerate *= 2;
	}
	int spanningEdge = vertexCount - 1;
	std::random_device rand_dev;
	std::uniform_int_distribution<int> weightDistr(weightFrom, weightTo);
	std::mt19937 generator(rand_dev());

	MyList* vertexList = new MyList();
	MyList* addedVertexList = new MyList();
	for (unsigned i = 0; i < vertexCount; i++) {
		vertexList->addAtEnd(i); //wierzcho³ki jeszcze nie dodane do grafu
	}
	std::uniform_int_distribution<int> distr(0, vertexList->getSize() - 1);
	addedVertexList->addAtBeginning(vertexList->removeAt(distr(generator)));

	//jeœli jestem w stanie wygenerowaæ drzewo spinaj¹ce tworze je
	if (edgesToGenerate >= spanningEdge) {
		for (int i = 0; i < spanningEdge; i++) {
			std::uniform_int_distribution<int> distr(0, vertexList->getSize() - 1);
			std::uniform_int_distribution<int> distr2(0, addedVertexList->getSize() - 1);
			//przek³adam wierzcho³ek z nieu¿ywany do u¿ytych
			int newVertex = vertexList->removeAt(distr(generator));
			int oldVertex = addedVertexList->getValueAt(distr2(generator));
			insertEdge(oldVertex, newVertex, weightDistr(generator));
			addedVertexList->addAtEnd(newVertex);
		}
		edgesToGenerate -= spanningEdge;
	}
	//Generuje wszystkie mo¿liwe krawêdzie które mogê dodaæ
	delete addedVertexList;
	delete vertexList;
	EdgeList *el = new EdgeList();
	unsigned jdelim = vertexCount;
	for (unsigned i = 0; i < vertexCount; i++) {
		if (!isDiGraph) {
			jdelim = i;
		}
		for (unsigned j = 0; j < jdelim; j++) {
			el->add(new Edge(i, j, weightDistr(generator)));
		}
	}
	//losuje z puli krawêdzi i dodaje a¿ do otrzymania po¿¹danej iloœci
	for (int i = 0; i < edgesToGenerate; i++) {
		std::uniform_int_distribution<int> edgeDistr(0, el->getSize() - 1);
		int pos = edgeDistr(generator);
		Edge* gen = el->pop(pos);
		bool exist = insertEdge(gen->v1, gen->v2, gen->weight);
		if (exist) {
			i--;
		}
		delete gen;
	}
	delete el;
}

void GraphRepresentationInterface::printMatrixGraph() {
	using namespace std;
	for (unsigned i = 0; i < vertexCount; i++) {
		for (unsigned j = 0; j < vertexCount; j++) {
			cout << setw(3);
			cout << searchEdge(i,j) << "  ";
		}
		cout << endl;
	}
}

void GraphRepresentationInterface::printListGraph() {
	using namespace std;
	for (unsigned i = 0; i < vertexCount; i++) {
		cout << i << ": ";
		for (unsigned j = 0; j < vertexCount; j++) {
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