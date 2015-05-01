#pragma once
#include "stdafx.h"

class Edge {
public:
	int weight;
	int v1;
	int v2;
	Edge(int vertex1, int vertex2, int weight) {
		v1 = vertex1;
		v2 = vertex2;
		this->weight = weight;
	}
	~Edge() {

	}
};