#include "stdafx.h"
#include <iostream>
#include "MatrixGraphRepresentation.h"
#include "ListGraphRepresentation.h"
#include "MinimumSpanningTreeAlgoritm.h"

int _tmain(int argc, _TCHAR* argv[]) {
	using namespace std;
	char ch;
	bool isDigraph = false;
	GraphRepresentationInterface *graph = new MatrixGraphRepresentation(false, 1);
	GraphRepresentationInterface *graph2 = new MatrixGraphRepresentation(false, 1);
	MinimumSpanningTreeAlgoritm* mst = new MinimumSpanningTreeAlgoritm(graph);
	do {
		cin >> ch;
		switch (ch) {
		case 'k':
			graph2 = mst->makeKruskalMst(graph2);
			graph2->printMatrixGraph();
			break;
		case 'p':
			graph2 = mst->makePrimMst(graph2);
			graph2->printMatrixGraph();
			break;
		case 'g':
			graph->generateGraph(4, 0.99, 1, 50);
			break;
		case 'z':
			graph->loadFromFile();
			break;
		case 'm':
			graph->printMatrixGraph();
			break;
		case 'l':
			graph->printListGraph();
			break;
		case 'd':
			isDigraph = !isDigraph;
			cout << "digraf: " << isDigraph << endl;
			break;
		case '[':
			delete graph;
			graph = new MatrixGraphRepresentation(isDigraph, 0);
			break;
		case ']':
			delete graph;
			graph = new MatrixGraphRepresentation(isDigraph, 0);
			break;
		}
	} while (ch != 'q');
	delete graph;
	delete graph2;
	if (mst != NULL) {
		delete mst;
	}
	return 0;
}

