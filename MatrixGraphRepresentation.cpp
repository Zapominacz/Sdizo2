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
	for (int i = 0; i < vertexCount; i++) {
		matrix[i] = new int[vertexCount];
		for (int j = 0; j < vertexCount; j++) {
			matrix[i][j] = -1;
		}
	}
}

void MatrixGraphRepresentation::deleteMatrix() {
	for (int i = 0; i < vertexCount; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = NULL;
}

void MatrixGraphRepresentation::clear(unsigned vc) {
	if (vc != vertexCount) {
		deleteMatrix();
		vertexCount = vc;
		createMatrix();
	}
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			matrix[i][j] = -1;
		}
	}
}

bool MatrixGraphRepresentation::insertEdge(unsigned v, unsigned u, int weight) {
	bool exist = this->exist(v, u);
	if (!exist) {
		matrix[v][u] = weight;
		if (!isDiGraph) {
			matrix[u][v] = weight;
		}
		edgeCount++;
	}
	return exist;
}

bool MatrixGraphRepresentation::deleteEdge(unsigned v, unsigned u) {
	bool exist = this->exist(v, u);
	if (exist) {
		matrix[v][u] = -1;
		edgeCount--;
	}
	return exist;
}

unsigned MatrixGraphRepresentation::vertexDegree(unsigned vertex) {
	int result = 0;
	for (int i = 0; i < vertexCount; i++) {
		if (exist(vertex, i)) {
			result++;
		}
	}
	return result;
}

int MatrixGraphRepresentation::searchEdge(unsigned v, unsigned u) {
	return matrix[v][u];
}