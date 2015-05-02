#pragma once
#include "stdafx.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "UnionFind.h"
#include "Edge.h"
#include "EdgeStack.h"
#include "MyArray.h"
#include "MyHeap.h"

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makePrimMst(GraphRepresentationInterface* base) {
	base->clear(graph->getVertexCount());
	MyHeap *heap = new MyHeap();
	heap->push(0, 0);
	for (int i = 1; i < graph->getVertexCount(); i++) {
		heap->push(10000, i);
	}
	while (heap->getSize() > 0) {
		int u = heap->pop();
		EdgeList *adjList = graph->getAdjFor(u);
		for (int i = 0; i < graph->vertexDegree(u); i++) {
			int v = adjList->getVal(i).v2;
			if (graph->vertexDegree(v) == 0) {
				int weight = graph->searchEdge(v, u);
				if (weight < heap->getKey(v)) {
					heap->setKey(v, weight);
					graph->insertEdge(u, v, weight);
				}
			}
		}
	}
	return base;
}

GraphRepresentationInterface* MinimumSpanningTreeAlgoritm::makeKruskalMst(GraphRepresentationInterface* base) {
	base->clear(graph->getVertexCount());
	UnionFind *unionFind = new UnionFind(graph->getVertexCount());
	EdgeStack *edges = new EdgeStack(graph);
	for(int i = 0; i < graph->getEdgeCount(); i++) {
		Edge edge = edges->pop();
		if (unionFind->isNotTheSameUnion(edge.v1, edge.v2)) {
			base->insertEdge(edge.v1, edge.v2, edge.weight);
			unionFind->merge(edge.v1, edge.v2);
		}
	}
	return base;
}