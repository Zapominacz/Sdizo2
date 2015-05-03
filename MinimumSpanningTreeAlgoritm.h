#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
/** klasa znajduj¹ca drzewo MST dla danego grafu*/
class MinimumSpanningTreeAlgoritm {
public:
	MinimumSpanningTreeAlgoritm();
	MinimumSpanningTreeAlgoritm(GraphRepresentationInterface* graph);
	~MinimumSpanningTreeAlgoritm();
	GraphRepresentationInterface* makePrimMst(GraphRepresentationInterface*);
	GraphRepresentationInterface* makeKruskalMst(GraphRepresentationInterface*);
	void loadGraph(GraphRepresentationInterface* graph);
private:
	GraphRepresentationInterface* graph;
};