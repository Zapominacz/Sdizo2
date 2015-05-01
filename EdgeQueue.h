#pragma once
#include "stdafx.h"

class EdgeQueue {
public:
	EdgeQueue(GraphRepresentationInterface*);
	~EdgeQueue();
	unsigned getSize() { return size; }
	Edge getMin(unsigned);
private:
	unsigned size;

};