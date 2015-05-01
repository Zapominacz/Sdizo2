#pragma once
#include "stdafx.h"
#include "MyList.h"

class GraphRepresentationInterface {
protected:
	unsigned int vertexCount;
	unsigned int edgeCount;
	bool isDiGraph;
public:
	GraphRepresentationInterface(bool, unsigned int);
	virtual ~GraphRepresentationInterface() {}
	virtual bool insertEdge(unsigned, unsigned, unsigned) = 0;
	virtual void clear(void) = 0;
	virtual bool deleteEdge(unsigned, unsigned) = 0;
	virtual bool vertexDegree(unsigned, unsigned) = 0;
	virtual bool searchEdge(unsigned, unsigned) = 0;
	virtual void printGraph(void) = 0;
	virtual void generateGraph(const unsigned int, float, const int, const int);
};