#include "stdafx.h"
#include "GraphRepresentationInterface.h"

class ShortestWayAlgoritm {
public:
	ShortestWayAlgoritm();
	ShortestWayAlgoritm(GraphRepresentationInterface* graph);
	~ShortestWayAlgoritm();
	GraphRepresentationInterface* makeDikstra(GraphRepresentationInterface*);
	GraphRepresentationInterface* makeBellman(GraphRepresentationInterface*);
	void loadGraph(GraphRepresentationInterface*);
private:
	GraphRepresentationInterface* graph;
};