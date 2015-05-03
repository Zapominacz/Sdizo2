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
		delete[] distances; //czyszcze poprzedne odleg�o�ci
	}
	distances = new int[vCount];
	//tablice pomocnicze do generowania grafu wyniku
	int *incidences = new int[vCount];
	int *weightBuf = new int[vCount];
	//poczakowo wszystkie drogi maj� warto�� INF
	for (unsigned i = 0; i < vCount; i++) {
		incidences[i] = -1;
		distances[i] = INF;
	}
	weightBuf[startVertex] = -1;
	incidences[startVertex] = startVertex;
	distances[startVertex] = 0;
	//przechowuje kraw�dzie w kopcu
	MyHeap* heap = new MyHeap();
	heap->push(startVertex, 0);
	for (unsigned i = 0; i < vCount; i++) {
		if (i == startVertex) {
			continue;
		} else {
			heap->push(INF, i);
		}
	}
	while (heap->getSize() > 0) {
		int key = heap->seekKey();
		int u = heap->pop(); //wyci�gam wierzcho�ek o najmneijszej wadze i pobieram jego s�siednie wierzcho�ki
		EdgeList* adjList = graph->getSimpleAdjFor(u);
		unsigned adjListSize = adjList->getSize();
		for (unsigned i = 0; i < adjListSize; i++) {
			Edge* tmp = adjList->pop(0);
			int v = tmp->v2;
			int weight = tmp->weight;
			int key2 = heap->getKey(v);
			if (key + weight < key2) { //zgodnie z nier�wno�ci� tr�jk�ta je�li droga jest lepsza
				heap->setKey(v, key + weight); //zast�puje najkr�tsz� tras� do tego wierzcho�ka now�
				weightBuf[v] = weight;
				distances[v] = key + weight;
				incidences[v] = u; //aktualizuje zmienne pomocnicze
			}
			delete tmp;
		}
		delete adjList;
	}
	for (unsigned i = 0; i < vCount; i++) {
		if (incidences[i] >= 0) {
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
	weightBuf[startVertex] = -1;
	for (unsigned i = 0; i < vCount; i++) {
		distances[i] = INF;
	}
	incidences[startVertex] = startVertex;//zmienne pomocnicze i ich inicjalizacja
	distances[startVertex] = 0;
	
	for (unsigned i = 0; i < vCount; i++) {
		for (unsigned j = 0; j < vCount; j++) {
			int w = graph->searchEdge(i, j);
			if (w > -1) { //iteruje po wszystkich mo�liwych kraw�dziach, je�li istnieje
				if (distances[i] < INF && distances[i] + w < distances[j]) { //sprawdzam czy jest to lepsza droga z pocz�tkowego
					distances[j] = distances[i] + w; //wierzcho�ka i je�li tak, zamieniam
					incidences[j] = i;
					weightBuf[j] = w;
				}
			}
		}
	}
	for (unsigned i = 0; i < vCount; i++) {
		base->insertEdge(incidences[i], i, weightBuf[i]); //tworze graf wyniku
	}
	delete[] weightBuf;
	delete[] incidences;
	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}