#pragma once
#include "GraphRepresentationInterface.h"

class MatrixGraphRepresentation : public GraphRepresentationInterface {
public:
	MatrixGraphRepresentation(bool, unsigned int);
	virtual ~MatrixGraphRepresentation() {}
private:
	unsigned int **matrix;
};