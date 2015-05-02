#include "stdafx.h"
#include <iostream>
#include "MatrixGraphRepresentation.h"
#include "ListGraphRepresentation.h"
#include "MinimumSpanningTreeAlgoritm.h"

int _tmain(int argc, _TCHAR* argv[]) {
	using namespace std;
	char ch;
	bool isDigraph = false;
	GraphRepresentationInterface *graph2, *graph = new MatrixGraphRepresentation(false, 1);
	MinimumSpanningTreeAlgoritm* mst = NULL;
	do {
		cin >> ch;
		switch (ch) {
		case 'p':
			mst = new MinimumSpanningTreeAlgoritm(graph);
			graph2 = mst->makeKruskalMst(new MatrixGraphRepresentation(false, 1));
			graph2->printMatrixGraph();
			delete graph2;
			break;
		case 'g':
			graph->generateGraph(10, 0.5, 1, 50);
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
	delete mst;
	return 0;
}

