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
		delete[] distances; //czyszcze poprzedne odleg³oœci
	}
	distances = new int[vCount];
	//tablice pomocnicze do generowania grafu wyniku
	int *incidences = new int[vCount];
	int *weightBuf = new int[vCount];
	//poczakowo wszystkie drogi maj¹ wartoœæ INF
	for (unsigned i = 0; i < vCount; i++) {
		incidences[i] = -1;
		weightBuf[i] = -1;
		distances[i] = INF;
	}
	incidences[startVertex] = startVertex;
	distances[startVertex] = 0;
	//przechowuje krawêdzie w kopcu
	MyHeap* heap = new MyHeap();
	heap->push(0, startVertex);
	for (unsigned i = 0; i < vCount; i++) {
		if (i == startVertex) {
			continue;
		} else {
			heap->push(INF, i);
		}
	}
	while (heap->getSize() > 0) {
		int key = heap->seekKey();
		int u = heap->pop(); //wyci¹gam wierzcho³ek o najmneijszej wadze i pobieram jego s¹siednie wierzcho³ki
		EdgeList* adjList = graph->getSimpleAdjFor(u);
		unsigned adjListSize = adjList->getSize();
		for (unsigned i = 0; i < adjListSize; i++) {
			Edge* tmp = adjList->pop(0);
			int v = tmp->v2;
			int weight = tmp->weight;
			int key2 = heap->getKey(v);
			if (key + weight < key2) { //zgodnie z nierównoœci¹ trójk¹ta jeœli droga jest lepsza
				heap->setKey(v, key + weight); //zastêpuje najkrótsz¹ trasê do tego wierzcho³ka now¹
				weightBuf[v] = weight;
				distances[v] = key + weight;
				incidences[v] = u; //aktualizuje zmienne pomocnicze
			}
			delete tmp;
		}
		delete adjList;
	}
	for (unsigned i = 0; i < vCount; i++) {
		if (incidences[i] > -1 && weightBuf[i] > -1) {
			base->insertEdge(incidences[i], i, weightBuf[i]);
		}
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
	
	for (unsigned i = 0; i < vCount; i++) {
		incidences[i] = -1;
		weightBuf[i] = -1;
		distances[i] = INF;
	}
	incidences[startVertex] = startVertex;//zmienne pomocnicze i ich inicjalizacja
	distances[startVertex] = 0;
	
	Edge* el = graph->getAllEdges();

	for (unsigned i = 0; i < vCount; i++) {
		for (unsigned j = 0; j < graph->getEdgeCount(); j++) {
			unsigned v1 = el[j].v1;
			unsigned v2 = el[j].v2;
			unsigned w = el[j].weight;
			if (distances[v1] < INF && distances[v1] + w < distances[v2]) { //sprawdzam czy jest to lepsza droga z pocz¹tkowego
				distances[v2] = distances[v1] + w; //wierzcho³ka i jeœli tak, zamieniam
				incidences[v2] = v1;
				weightBuf[v2] = w;
			}
		}
		
	}
	for (unsigned i = 0; i < vCount; i++) {
		if (incidences[i] > -1 && weightBuf[i] > -1) {
			base->insertEdge(incidences[i], i, weightBuf[i]); //tworze graf wyniku
		}
	}
	delete[] el;
	delete[] weightBuf;
	delete[] incidences;
	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}