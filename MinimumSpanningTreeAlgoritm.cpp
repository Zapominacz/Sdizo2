#pragma once
#include "stdafx.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "UnionFind.h"
#include "MyHeap.h"

MinimumSpanningTreeAlgoritm::MinimumSpanningTreeAlgoritm() {
	loadGraph(NULL);
}

MinimumSpanningTreeAlgoritm::MinimumSpanningTreeAlgoritm(GraphRepresentationInterface* graph) {
	loadGraph(graph);
}

MinimumSpanningTreeAlgoritm::~MinimumSpanningTreeAlgoritm() {
	graph = NULL;
}

void MinimumSpanningTreeAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makePrimMst(GraphRepresentationInterface* base) {
	const int INF = 100000;
	unsigned vCount = graph->getVertexCount();
	base->clear(vCount);
	MyHeap *heap = new MyHeap();
	bool *addedVertexes = new bool[vCount];
	int *x = new int[vCount]; //pomocnicza lista do generowania grafu wyniku
	int *w = new int[vCount]; //pomocnicza lista rzeczywistych wag
	x[0] = -2;
	heap->push(0, 0);
	for (unsigned i = 1; i < vCount; i++) { //dodaje krawêdzie wraz z ich wagami w kopcu
		heap->push(INF, i);
		addedVertexes[i] = false;
	}
	while (heap->getSize() > 0) {
		int u = heap->pop();
		addedVertexes[u] = true;
		EdgeList *adjList = graph->getSimpleAdjFor(u);
		unsigned eSize = adjList->getSize(); //pobieram listê s¹siaduj¹cych krawêdzi z danycm wierzcho³kiem
		for (unsigned i = 0; i < eSize; i++) {
			Edge *e = adjList->pop(0);
			int v = e->v2;
			int weight = e->weight;
			if (!addedVertexes[v]) { //jeœli nie zosta³ dodany
				if (weight < heap->getKey(v)) { //i jego waga krawêdzi jest mniejsza od wagi w kopcu
					heap->setKey(v, weight); //zmieniam wagê
					x[v] = u; //dodaje do pomocniczych list
					w[v] = weight;
				}
			}
			delete e;
		}
		delete adjList;
	}
	for (unsigned i = 0; i < vCount; i++) {
		if (x[i] != -2) { //generuje graf wyniku
			base->insertEdge(i, x[i], w[i]);
		}
	}
	delete[] addedVertexes;
	delete[] x;
	delete[] w;
	delete heap;
	return base;
}

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makeKruskalMst(GraphRepresentationInterface* base) {
	base->clear(graph->getVertexCount());
	UnionFind *unionFind = new UnionFind(graph->getVertexCount()); //tworze podrzewa
	EdgeStack *edges = new EdgeStack();
	for (unsigned i = 0; i < graph->getVertexCount(); i++) {
		for (unsigned j = 0; j < i; j++) {
			int weight = graph->searchEdge(i, j); //sortuje 
			if (weight > -1) {
				edges->push(new Edge(i, j, weight));
			}
		}
	}
	for (unsigned i = 0; i < graph->getEdgeCount(); i++) {
		Edge *edge = edges->pop();
		if (unionFind->isNotTheSameUnion(edge->v1, edge->v2)) { //³¹cze podrzewa i dodaje krawêdŸ
			base->insertEdge(edge->v1, edge->v2, edge->weight); //jeœli nie tworz¹ cyklu
			unionFind->merge(edge->v1, edge->v2);
		}
		delete edge;
	}
	return base;
}