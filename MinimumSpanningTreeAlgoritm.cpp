#pragma once
#include "stdafx.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "UnionFind.h"
#include "MyArray.h"
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
	int vCount = graph->getVertexCount();
	base->clear(vCount);
	MyHeap *heap = new MyHeap();
	bool *addedVertexes = new bool[vCount];
	int *x = new int[vCount];
	int *w = new int[vCount];
	x[0] = -2;
	heap->push(0, 0);
	for (unsigned i = 1; i < vCount; i++) {
		heap->push(INF, i);
		addedVertexes[i] = false;
	}
	while (heap->getSize() > 0) {
		int u = heap->pop();
		addedVertexes[u] = true;
		EdgeStack *adjList = graph->getAdjFor(u);
		int eSize = adjList->getSize();
		for (unsigned i = 0; i < eSize; i++) {
			Edge *e = adjList->pop();
			int v = e->v2;
			int weight = e->weight;
			if (!addedVertexes[v]) {
				if (weight < heap->getKey(v)) {
					heap->setKey(v, weight);
					x[v] = u;
					w[v] = weight;
				}
			}
			delete e;
		}
		delete adjList;
	}
	for (int i = 0; i < vCount; i++) {
		if (x[i] != -2) {
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
	UnionFind *unionFind = new UnionFind(graph->getVertexCount());
	EdgeStack *edges = new EdgeStack();
	for (unsigned i = 0; i < graph->getVertexCount(); i++) {
		for (unsigned j = 0; j < i; j++) {
			int weight = graph->searchEdge(i, j);
			if (weight > -1) {
				edges->push(new Edge(i, j, weight));
			}
		}
	}
	for (unsigned i = 0; i < graph->getEdgeCount(); i++) {
		Edge *edge = edges->pop();
		if (unionFind->isNotTheSameUnion(edge->v1, edge->v2)) {
			base->insertEdge(edge->v1, edge->v2, edge->weight);
			unionFind->merge(edge->v1, edge->v2);
		}
		delete edge;
	}
	return base;
}