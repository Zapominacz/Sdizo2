#pragma once
#include "stdafx.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "UnionFind.h"
#include "Edge.h"
#include "EdgeStack.h"
#include "MyArray.h"
#include "MyHeap.h"

MinimumSpanningTreeAlgoritm::MinimumSpanningTreeAlgoritm() {
	loadGraph(NULL);
}

MinimumSpanningTreeAlgoritm::MinimumSpanningTreeAlgoritm(GraphRepresentationInterface* graph) {
	loadGraph(graph);
}

MinimumSpanningTreeAlgoritm::~MinimumSpanningTreeAlgoritm() {
	if (graph != NULL) {
		delete graph;
	}
}

void MinimumSpanningTreeAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makePrimMst(GraphRepresentationInterface* base) {
	base->clear(graph->getVertexCount());
	MyHeap *heap = new MyHeap();
	heap->push(0, 0);
	for (unsigned i = 1; i < base->getVertexCount(); i++) {
		heap->push(10000, i);
	}
	while (heap->getSize() > 0) {
		int u = heap->pop();
		EdgeStack *adjList = graph->getAdjFor(u);
		for (unsigned i = 0; i < adjList->getSize(); i++) {
			Edge e = adjList->pop();
			int v = e.v2;
			int weight = e.weight;
			if (base->vertexDegree(v) == 0) {
				if (weight < heap->getKey(v)) {
					heap->setKey(v, weight);
					base->insertEdge(u, v, weight);
				}
			}
		}
	}
	return base;
}

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makeKruskalMst(GraphRepresentationInterface* base) {
	base->clear(graph->getVertexCount());
	UnionFind *unionFind = new UnionFind(graph->getVertexCount());
	EdgeStack *edges = new EdgeStack();
	for (unsigned i = 0; i < graph->getVertexCount(); i++) {
		for (int j = 0; j < i; j++) {
			int weight = graph->searchEdge(i, j);
			if (weight > -1) {
				edges->push(Edge(i, j, weight));
			}
		}
	}
	for (unsigned i = 0; i < graph->getEdgeCount(); i++) {
		Edge edge = edges->pop();
		if (unionFind->isNotTheSameUnion(edge.v1, edge.v2)) {
			base->insertEdge(edge.v1, edge.v2, edge.weight);
			unionFind->merge(edge.v1, edge.v2);
		}
	}
	return base;
}