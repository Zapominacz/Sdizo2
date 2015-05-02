#include "stdafx.h"
#include "MatrixGraphRepresentation.h"
#include "ListGraphRepresentation.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "ShortestWayAlgoritm.h"

int _tmain(int argc, _TCHAR* argv[]) {
	using namespace std;
	char ch;
	bool isDigraph = false;
	GraphRepresentationInterface *graph = new ListGraphRepresentation(false, 1);
	GraphRepresentationInterface *graph2 = new ListGraphRepresentation(false, 1);
	MinimumSpanningTreeAlgoritm* mst = new MinimumSpanningTreeAlgoritm(graph);
	ShortestWayAlgoritm *sw = new ShortestWayAlgoritm(graph, 0);
	do {
		cin >> ch;
		switch (ch) {
		case 'k':
			graph2 = mst->makeKruskalMst(graph2);
			graph2->printMatrixGraph();
			break;
		case 'd':
			graph2 = sw->makeDikstra(graph2);
			graph2->printMatrixGraph();
			break;
		case 'b':
			graph2 = sw->makeBellman(graph2);
			graph2->printMatrixGraph();
			delete sw;
			break;
		case 'p':
			graph2 = mst->makePrimMst(graph2);
			graph2->printMatrixGraph();
			break;
		case 'g':
			graph->generateGraph(4, 0.99f, 1, 50);
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
		case 'i':
			isDigraph = !isDigraph;
			cout << "isDigraf: " << isDigraph << endl;
			break;
		case '[':
			delete graph;
			graph = new MatrixGraphRepresentation(isDigraph, 1);
			break;
		case ']':
			delete graph;
			graph = new ListGraphRepresentation(isDigraph, 1);
			break;
		}
	} while (ch != 'q');
	delete graph;
	delete graph2;
	delete mst;
	delete sw;
	return 0;
}

