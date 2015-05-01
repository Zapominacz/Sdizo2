#pragma once
#include "stdafx.h"
#include "GraphRepresentationInterface.h"

class MatrixGraphRepresentation : public GraphRepresentationInterface {
public:
	MatrixGraphRepresentation(bool, unsigned int);
	virtual ~MatrixGraphRepresentation();
	virtual bool insertEdge(unsigned int, unsigned int, int);
	virtual void clear(void);
	virtual bool deleteEdge(unsigned, unsigned);
	virtual unsigned vertexDegree(unsigned);
	virtual int searchEdge(unsigned, unsigned);
	inline bool exist(unsigned v, unsigned u) { return matrix[v][u] > -1; }
private:
	int** matrix;
};