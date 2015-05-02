#include "stdafx.h"
#include "ShortestWayAlgoritm.h"
#include "MyHeap.h"


ShortestWayAlgoritm::ShortestWayAlgoritm() {
	loadGraph(NULL);
}

ShortestWayAlgoritm::ShortestWayAlgoritm(GraphRepresentationInterface* graph) {
	loadGraph(graph);
}

ShortestWayAlgoritm::~ShortestWayAlgoritm() {
	graph = NULL;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeDikstra(GraphRepresentationInterface* base) {
	const int INF = 10000;
	base->clear(graph->getVertexCount());
	MyHeap *heap = new MyHeap();
	heap->push(0, 0);
	for (unsigned i = 1; i < base->getVertexCount(); i++) {
		heap->push(INF, i);
	}
	while (heap->getSize() > 0) {
		int w = heap->seekKey();
		int u = heap->pop();
		EdgeStack *adjList = graph->getAdjFor(u);
		for (unsigned i = 0; i < adjList->getSize(); i++) {
			Edge tmp = adjList->pop();
			int v = tmp.v2;
			int d = tmp.weight;
			if (base->vertexDegree(v) == 0) {
				if (w + d < heap->getKey(v)) {
					heap->setKey(v, w + d);
					base->insertEdge(u, v, d);
				}
			}
		}
	}
	return base;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeBellman(GraphRepresentationInterface* base) {
	const int INF = 10000;

	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}