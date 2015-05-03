#pragma once
#include "stdafx.h"
#include "ShortestWayAlgoritm.h"
#include "MyHeap.h"


ShortestWayAlgoritm::ShortestWayAlgoritm() {
	loadGraph(NULL);
	distances = NULL;
}

ShortestWayAlgoritm::ShortestWayAlgoritm(GraphRepresentationInterface* graph, unsigned v) {
	loadGraph(graph);
	setStartVertex(v);
	distances = NULL;
}

ShortestWayAlgoritm::~ShortestWayAlgoritm() {
	graph = NULL;
	if (distances != NULL) {
		delete distances;
		distances = NULL;
	}
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeDikstra(GraphRepresentationInterface* base) {
	int INF = 10000;
	unsigned vCount = graph->getVertexCount();
	base->clear(vCount);
	if (distances != NULL) {
		delete[] distances;
	}
	distances = new int[vCount];
	int *incidences = new int[vCount];
	int *weightBuf = new int[vCount];

	for (unsigned i = 0; i < vCount; i++) {
		distances[i] = INF;
	}
	weightBuf[startVertex] = -1;
	incidences[startVertex] = startVertex;
	distances[startVertex] = 0;

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
			if (key + weight < heap->getKey(v)) {
				heap->setKey(v, key + weight);
				weightBuf[v] = weight;
				distances[v] = weight + distances[u];
				incidences[v] = u;
			}
			delete tmp;
		}
		delete adjList;
	}
	for (unsigned i = 0; i < vCount; i++) {
		base->insertEdge(incidences[i], i, weightBuf[i]);
	}
	delete[] weightBuf;
	delete[] incidences;
	delete heap;
	return base;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeBellman(GraphRepresentationInterface* base) {
	int INF = 10000;
	unsigned vCount = graph->getVertexCount();
	base->clear(vCount);
	if (distances != NULL) {
		delete[] distances;
	}
	distances = new int[vCount];
	int *incidences = new int[vCount];
	int *weightBuf = new int[vCount];
	weightBuf[startVertex] = -1;
	for (unsigned i = 0; i < vCount; i++) {
		distances[i] = INF;
	}
	incidences[startVertex] = startVertex;
	distances[startVertex] = 0;

	for (unsigned i = 0; i < vCount; i++) {
		for (unsigned j = 0; j < vCount; j++) {
			int w = graph->searchEdge(i, j);
			if (w > -1) {
				if (distances[i] < INF && distances[i] + w < distances[j]) {
					distances[j] = distances[i] + w;
					incidences[j] = i;
					weightBuf[j] = w;
				}
			}
		}
	}
	for (unsigned i = 0; i < vCount; i++) {
		base->insertEdge(incidences[i], i, weightBuf[i]);
	}
	delete[] weightBuf;
	delete[] incidences;
	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}