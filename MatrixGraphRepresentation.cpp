#pragma once
#include "stdafx.h"
#include "MatrixGraphRepresentation.h"

MatrixGraphRepresentation::MatrixGraphRepresentation(bool isDigraph, unsigned int vertexCount)
	: GraphRepresentationInterface(isDigraph, vertexCount) {
	createMatrix();
}

MatrixGraphRepresentation::~MatrixGraphRepresentation() {
	deleteMatrix();
}

void MatrixGraphRepresentation::createMatrix() {
	matrix = new int*[vertexCount];
	for (unsigned i = 0; i < vertexCount; i++) {
		matrix[i] = new int[vertexCount];
		for (unsigned j = 0; j < vertexCount; j++) {
			matrix[i][j] = -1;
		}
	}
}

void MatrixGraphRepresentation::deleteMatrix() {
	for (unsigned i = 0; i < vertexCount; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = NULL;
}

void MatrixGraphRepresentation::clear(unsigned vc) {
	deleteMatrix();
	edgeCount = 0;
	vertexCount = vc;
	createMatrix();
}

bool MatrixGraphRepresentation::insertEdge(unsigned v, unsigned u, int weight) {
	if (v < vertexCount && u < vertexCount) {
		bool exist = this->exist(v, u);
		if (!exist) {
			matrix[v][u] = weight;
			if (!isDiGraph) {
				matrix[u][v] = weight;
			}
			edgeCount++;
		}
		return exist;
	} else {
		printf("zla krawedz");
		return false;
	}
}

bool MatrixGraphRepresentation::deleteEdge(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		bool exist = this->exist(v, u);
		if (exist) {
			matrix[v][u] = -1;
			edgeCount--;
		}
		return exist;
	} else {
		printf("zla krawedz");
		return false;
	}
}

unsigned MatrixGraphRepresentation::vertexDegree(unsigned vertex) {
	if (vertex < vertexCount) {
		int result = 0;
		for (unsigned i = 0; i < vertexCount; i++) {
			if (exist(vertex, i)) {
				result++;
			}
		}
		return result;
	} else {
		return -1;
	}
}

bool MatrixGraphRepresentation::exist(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		return matrix[v][u] > -1;
	}
	else {
		printf("zla krawedz");
		return false;
	}
}

int MatrixGraphRepresentation::searchEdge(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		return matrix[v][u];
	} else {
		 printf("err");
		 return-2;
	}
	
}

EdgeStack* MatrixGraphRepresentation::getAdjFor(unsigned v) {
	if (v < vertexCount) {
		EdgeStack *result = new EdgeStack();
		for (unsigned i = 0; i < vertexCount; i++) {
			if (matrix[v][i] > -1) {
				result->push(new Edge(v, i, matrix[v][i]));
			}
		}
		return result;
	} else {
		 printf("err");
		 return NULL;
	}
}

EdgeList* MatrixGraphRepresentation::getSimpleAdjFor(unsigned v) {
	if (v < vertexCount) {
		EdgeList *result = new EdgeList();
		for (unsigned i = 0; i < vertexCount; i++) {
			if (matrix[v][i] > -1) {
				result->addAtBeginning(new Edge(v, i, matrix[v][i]));
			}
		}
		return result;
	} else {
		printf("err");
		return NULL;
	}
}

Edge* MatrixGraphRepresentation::getAllEdges() {
	Edge* result = new Edge[edgeCount];
	int count = 0;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			if (matrix[i][j] > -1) {
				Edge e = Edge(i, j, matrix[i][j]);
				result[count] = e;
				count++;
			}
		}
	}
	return result;
}