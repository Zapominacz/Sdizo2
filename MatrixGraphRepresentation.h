#pragma once
#include "GraphRepresentationInterface.h"

class MatrixGraphRepresentation : public GraphRepresentationInterface {
public:
	MatrixGraphRepresentation(bool, unsigned int);
	virtual ~MatrixGraphRepresentation() {}
	virtual bool insertEdge(unsigned v, unsigned u);
	virtual bool deleteEdge(unsigned v, unsigned u);
	virtual bool vertexDegree(unsigned v, unsigned u);
	virtual bool searchEdge(unsigned v, unsigned u);
private:
	unsigned int **matrix;
};