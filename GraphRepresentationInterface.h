#pragma once
#include "stdafx.h"
#include "EdgeList.h"

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
	virtual EdgeList* getAdjFor(unsigned) = 0;
	virtual void printListGraph(void);
	virtual void loadFromFile(void);
	virtual void printMatrixGraph(void);
	virtual void generateGraph(const unsigned int, float, const int, const int);
	unsigned getVertexCount(void) { return vertexCount;  }
	unsigned getEdgeCount(void) { return edgeCount; }
};