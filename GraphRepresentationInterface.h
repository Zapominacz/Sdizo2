#pragma once
#include "stdafx.h"
#include "EdgeList.h"
#include "EdgeStack.h"
#include "Edge.h"
/** Klasa reprezentująca dowonly graf*/
class GraphRepresentationInterface {
protected:
	unsigned int vertexCount;
	unsigned int edgeCount;
	bool isDiGraph;
public:
	GraphRepresentationInterface(bool, unsigned int);
	virtual ~GraphRepresentationInterface() {}
	virtual bool insertEdge(unsigned int, unsigned int, int) = 0;
	virtual void clear(unsigned) = 0;
	virtual bool deleteEdge(unsigned, unsigned) = 0;
	virtual unsigned vertexDegree(unsigned) = 0;
	virtual int searchEdge(unsigned, unsigned) = 0;
	virtual EdgeStack* getAdjFor(unsigned) = 0;
	virtual EdgeList* getSimpleAdjFor(unsigned) = 0;
	virtual void printListGraph(void);
	virtual void loadFromFile(void);
	virtual void printMatrixGraph(void);
	virtual Edge* getAllEdges(void) = 0;
	virtual void generateGraph(const unsigned int, float, const int, const int);
	unsigned getVertexCount(void) { return vertexCount;  }
	unsigned getEdgeCount(void) { return edgeCount; }
	void setDigraph(bool digraph) { isDiGraph = digraph; }
	bool isDigraph() { return isDiGraph; }
};