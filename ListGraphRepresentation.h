#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
/** implementacja grafu jaka lista s¹siedztwa*/
class ListGraphRepresentation : public GraphRepresentationInterface {
public:
	ListGraphRepresentation(bool, unsigned int);
	virtual ~ListGraphRepresentation();
	virtual bool insertEdge(unsigned int, unsigned int, int);
	virtual void clear(unsigned);
	virtual bool deleteEdge(unsigned, unsigned);
	virtual unsigned vertexDegree(unsigned);
	virtual int searchEdge(unsigned, unsigned);
	virtual EdgeStack* getAdjFor(unsigned);
	virtual EdgeList* getSimpleAdjFor(unsigned);
private:
	EdgeList** edgesList;
	void removeLists(void);
	void createLists(void);
};