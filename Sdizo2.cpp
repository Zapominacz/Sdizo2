#include "stdafx.h"
#include "MatrixGraphRepresentation.h"
#include "ListGraphRepresentation.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "ShortestWayAlgoritm.h"
#include <fstream>
#include "Timer.h"

void presentation() {
	using namespace std;
	bool mode = false;
	bool matrix = false;
	int v;
	float d;
	char ch;
	bool algoritm = false;

	GraphRepresentationInterface *graph = NULL;
	GraphRepresentationInterface *graph2 = NULL;
	MinimumSpanningTreeAlgoritm* mst = NULL;
	ShortestWayAlgoritm *sw = NULL;
	do {
		if (!mode) {
			cout << "1: Macierzowo\n2:Listowo\nq: wyjscie" << endl;
			cin >> ch;
			if (graph != NULL) {
				delete graph;
				graph = NULL;
			}
			if (graph2 != NULL) {
				delete graph2;
				graph2 = NULL;
			}
			switch (ch) {
			case'1':
				mode = true;
				matrix = true;
				graph = new MatrixGraphRepresentation(true, 1);
				graph2 = new MatrixGraphRepresentation(true, 1);
			case'2':
				mode = true;
				matrix = false;
				graph = new ListGraphRepresentation(true, 1);
				graph2 = new ListGraphRepresentation(true, 1);
			case'q':
				return;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
		if (!algoritm) {
			cout << "q: wyjdz\n1: prim i kruskal (MST)\n2: dijkstra i bellman (Droga)" << endl;
			cin >> ch;
			if (mst != NULL) {
				delete mst;
				mst = NULL;
			}
			if (sw != NULL) {
				delete sw;
				sw = NULL;
			}
			switch (ch) {
			case'q':
				mode = false;
				continue;
			case'1':
				graph->setDigraph(false);
				mst = new MinimumSpanningTreeAlgoritm(graph);
				algoritm = true;
				break;
			case'2':
				graph->setDigraph(true);
				sw = new ShortestWayAlgoritm(graph, 0);
				algoritm = true;
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
		else if (mst != NULL) {
			cout << "q: wyjscie\n1: Wczytaj\n2: Prim\n3: Kruskal\n4: Pokaz\n5: generuj" << endl;
			cin >> ch;
			switch (ch) {
			case'q':
				algoritm = false;
				continue;
			case'1':
				graph->loadFromFile();
			case'2':
				graph2 = mst->makePrimMst(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
			case'3':
				graph2 = mst->makeKruskalMst(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
			case'4':
				if (matrix) {
					graph->printMatrixGraph();
				}
				else {
					graph->printListGraph();
				}
				break;
			case'5':
				cout << "Ilosc wierzcholkow:" << endl;
				cin >> v;
				cout << "Gestosc < 1:" << endl;
				cin >> d;
				graph->generateGraph(v, d, 1, 50);
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
		else if (sw != NULL) {
			cout << "q: wyjscie\n1: Wczytaj\n2: Djikstra\n3: Ford-Bellman\n4: Pokaz\n5: generuj\n6: poczatek" << endl;
			cin >> ch;
			switch (ch) {
			case'q':
				algoritm = false;
				continue;
			case'1':
				graph->loadFromFile();
			case'2':
				graph2 = sw->makeDikstra(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
			case'3':
				graph2 = sw->makeBellman(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
			case'4':
				if (matrix) {
					graph->printMatrixGraph();
				}
				else {
					graph->printListGraph();
				}
				break;
			case'5':
				cout << "Ilosc wierzcholkow:" << endl;
				cin >> v;
				cout << "Gestosc < 1:" << endl;
				cin >> d;
				graph->generateGraph(v, d, 1, 50);
				break;
			case'6':
				cout << "Punkt startowy:" << endl;
				cin >> v;
				sw->setStartVertex(v);
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
	} while (true);
}

void test() {
	using namespace std;
	int vCount[] = { 100, 500, 1000, 5000, 10000 };
	float dens[] = { 0.25, 0.5, 0.75, 0.99};
	int times = 150;

	fstream file("result.txt", std::ios_base::out);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			Timer *timer = new Timer();
			for (int k = 0; k < times; k++) {
				timer->startTimer;

				timer->stopTimer;
			}
			timer->nextMeasure;
			file << timer->getAvgTime();
			delete timer;
		}
	}



	file.close();
}

int _tmain(int argc, _TCHAR* argv[]) {
	presentation();
	test();
	return 0;
}

