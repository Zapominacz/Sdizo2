#include "stdafx.h"
#include "ShortestWayAlgoritm.h"


ShortestWayAlgoritm::ShortestWayAlgoritm() {
	loadGraph(NULL);
}

ShortestWayAlgoritm::ShortestWayAlgoritm(GraphRepresentationInterface* graph) {
	loadGraph(graph);
}

ShortestWayAlgoritm::~ShortestWayAlgoritm() {
	if (graph != NULL) {
		delete graph;
	}
	graph = NULL;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeDikstra(GraphRepresentationInterface* base) {

	return base;
}

GraphRepresentationInterface* ShortestWayAlgoritm::makeBellman(GraphRepresentationInterface* base) {

	return base;
}

void ShortestWayAlgoritm::loadGraph(GraphRepresentationInterface* graph) {
	this->graph = graph;
}