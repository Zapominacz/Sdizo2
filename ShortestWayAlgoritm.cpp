#include "stdafx.h"
#include "ShortestWayAlgoritm.h"
#include "MyHeap.h"


ShortestWayAlgoritm::ShortestWayAlgoritm() {
	loadGraph(NULL);
}

ShortestWayAlgoritm::ShortestWayAlgoritm(GraphRepresentationInterface* graph, unsigned v) {
	loadGraph(graph);
	setStartVertex(v);
}

ShortestWayAlgoritm::~ShortestWayAlgoritm() {
	graph = NULL;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeDikstra(GraphRepresentationInterface* base) {
	const int INF = 10000;
	base->clear(graph->getVertexCount());
	MyHeap *heap = new MyHeap();
	heap->push(startVertex, 0);
	for (unsigned i = 0; i < base->getVertexCount(); i++) {
		if (i = startVertex) {
			continue;
		} else {
			heap->push(INF, i);
		}
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
	unsigned vCount = graph->getVertexCount();
	base->clear(vCount);
	int *vWeights = new int[vCount];
	for (unsigned i = 0; i < vCount; i++) {
		vWeights[i] = INF;
	}
	vWeights[startVertex] = 0;
	for (unsigned i = 0; i < vCount; i++) {
		for (unsigned j = 0; j < graph->getEdgeCount(); j++) {
			int w = graph->searchEdge(i, j);
			if (w > -1) {
				if (vWeights[i] < INF && vWeights[i] + w < vWeights[j]) {
					vWeights[j] = vWeights[i] + w;
					base->insertEdge(i, j, w);
				}
			}
		}
	}
	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}