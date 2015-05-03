#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"
/** implementacja grafu jako macierz incydencji*/
class MatrixGraphRepresentation : public GraphRepresentationInterface {
public:
	MatrixGraphRepresentation(bool, unsigned int);
	virtual ~MatrixGraphRepresentation();
	virtual bool insertEdge(unsigned int, unsigned int, int);
	virtual void clear(unsigned);
	void createMatrix(void);
	void deleteMatrix(void);
	virtual bool deleteEdge(unsigned, unsigned);
	virtual unsigned vertexDegree(unsigned);
	virtual int searchEdge(unsigned, unsigned);
	virtual EdgeStack* getAdjFor(unsigned);
	virtual EdgeList* getSimpleAdjFor(unsigned);
	virtual bool exist(unsigned, unsigned);
private:
	int** matrix;
};