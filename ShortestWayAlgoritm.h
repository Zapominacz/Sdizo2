#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
/** Klasa wykonuj�ca algorytmy najkr�tszej drogi na podanym grafie*/
class ShortestWayAlgoritm {
public:
	ShortestWayAlgoritm();
	ShortestWayAlgoritm(GraphRepresentationInterface* graph, unsigned);
	~ShortestWayAlgoritm();
	GraphRepresentationInterface* makeDikstra(GraphRepresentationInterface*);
	GraphRepresentationInterface* makeBellman(GraphRepresentationInterface*);
	void loadGraph(GraphRepresentationInterface*);
	void setStartVertex(unsigned v) { startVertex = v; }
	int getDistanceTo(int v) { if (distances != NULL) return distances[v]; else return -1; }
private:
	GraphRepresentationInterface* graph;
	unsigned startVertex;
	int* distances;
};