#pragma once
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
	int INF = 10000;
	base->clear(graph->getVertexCount());
	MyHeap* heap = new MyHeap();
	heap->push(startVertex, 0);
	for (unsigned i = 0; i < base->getVertexCount(); i++) {
		if (i == startVertex) {
			continue;
		} else {
			heap->push(INF, i);
		}
	}
	while (heap->getSize() > 0) {
		int key = heap->seekKey();
		int u = heap->pop();
		EdgeStack* adjList = graph->getAdjFor(u);
		for (unsigned i = 0; i < adjList->getSize(); i++) {
			Edge* tmp = adjList->pop();
			int v = tmp->v2;
			int weight = tmp->weight;
			if (base->vertexDegree(v) == 0) {
				if (key + weight < heap->getKey(v)) {
					heap->setKey(v, key + weight);
					base->insertEdge(u, v, weight);
				}
			}
			delete tmp;
		}
		delete adjList;
	}
	delete heap;
	return base;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeBellman(GraphRepresentationInterface* base) {
	int INF = 10000;
	unsigned vCount = graph->getVertexCount();
	base->clear(vCount);
	int *vWeights = new int[vCount];
	int *x = new int[vCount];
	for (unsigned i = 0; i < vCount; i++) {
		vWeights[i] = INF;
	}
	x[startVertex] = startVertex;
	vWeights[startVertex] = 0;
	for (unsigned i = 0; i < vCount; i++) {
		for (unsigned j = 0; j < vCount; j++) {
			int w = graph->searchEdge(i, j);
			if (w > -1) {
				if (vWeights[i] < INF && vWeights[i] + w < vWeights[j]) {
					vWeights[j] = vWeights[i] + w;
					x[j] = i;
				}
			}
		}
	}
	for (unsigned i = 0; i < vCount; i++) {
		base->insertEdge(i, x[i], vWeights[i]);
	}
	delete[] vWeights;
	delete[] x;
	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}