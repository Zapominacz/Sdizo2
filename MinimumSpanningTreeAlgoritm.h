#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"

class MinimumSpanningTreeAlgoritm {
public:
	MinimumSpanningTreeAlgoritm(GraphRepresentationInterface* graph);
	~MinimumSpanningTreeAlgoritm();
	GraphRepresentationInterface* makePrimMst(GraphRepresentationInterface*);
	GraphRepresentationInterface* makeKruskalMst(GraphRepresentationInterface*);
	void loadGraph(GraphRepresentationInterface* graph);
private:
	GraphRepresentationInterface* graph;
};