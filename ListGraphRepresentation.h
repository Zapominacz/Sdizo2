#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
#include "EdgeList.h"

class ListGraphRepresentation : public GraphRepresentationInterface {
public:
	ListGraphRepresentation(bool, unsigned int);
	virtual ~ListGraphRepresentation() {}
	virtual bool insertEdge(unsigned int, unsigned int, int);
	virtual void clear(void);
	virtual bool deleteEdge(unsigned, unsigned);
	virtual unsigned vertexDegree(unsigned);
	virtual int searchEdge(unsigned, unsigned);
private:
	EdgeList** edgesList;
	void removeLists(void);
	void createLists(void);
};