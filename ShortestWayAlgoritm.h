#include "stdafx.h"
#include "GraphRepresentationInterface.h"

class ShortestWayAlgoritm {
public:
	ShortestWayAlgoritm();
	ShortestWayAlgoritm(GraphRepresentationInterface* graph, unsigned);
	~ShortestWayAlgoritm();
	GraphRepresentationInterface* makeDikstra(GraphRepresentationInterface*);
	GraphRepresentationInterface* makeBellman(GraphRepresentationInterface*);
	void loadGraph(GraphRepresentationInterface*);
	void setStartVertex(unsigned v) { startVertex = v; }
private:
	GraphRepresentationInterface* graph;
	unsigned startVertex;
};