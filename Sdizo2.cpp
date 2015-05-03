#include "stdafx.h"
#include "MatrixGraphRepresentation.h"
#include "ListGraphRepresentation.h"
#include "MinimumSpanningTreeAlgoritm.h"
#include "ShortestWayAlgoritm.h"
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
				break;
			case'2':
				mode = true;
				matrix = false;
				graph = new ListGraphRepresentation(true, 1);
				graph2 = new ListGraphRepresentation(true, 1);
				break;
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
				graph2->setDigraph(false);
				mst = new MinimumSpanningTreeAlgoritm(graph);
				algoritm = true;
				break;
			case'2':
				graph->setDigraph(true);
				graph2->setDigraph(true);
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
				break;
			case'2':
				graph2 = mst->makePrimMst(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
				break;
			case'3':
				graph2 = mst->makeKruskalMst(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
				break;
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
			cout << "q: wyjscie\n1: Wczytaj\n2: Djikstra\n3: Ford-Bellman\n4: Pokaz\n5: generuj\n6: poczatek\n7: odleglosci" << endl;
			cin >> ch;
			switch (ch) {
			case'q':
				algoritm = false;
				continue;
			case'1':
				graph->loadFromFile();
				break;
			case'2':
				graph2 = sw->makeDikstra(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
				break;
			case'3':
				graph2 = sw->makeBellman(graph2);
				cout << "Macierzowo:" << endl;
				graph2->printMatrixGraph();
				cout << "Listowo:" << endl;
				graph2->printListGraph();
				break;
			case'4':
				if (matrix) {
					graph->printMatrixGraph();
				} else {
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
			case'7':
				cout << "Odleglosci od pkt startowego:" << endl;
				for (unsigned i = 0; i < graph->getVertexCount(); i++) {
					cout << i << ": " << sw->getDistanceTo(i) << endl;
				}
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
	} while (true);
}

void test1() {
	using namespace std;
	int vCount[] = { 10, 50, 100, 500, 750 };
	float dens[] = { 0.25f, 0.5f, 0.75f, 0.99f };
	int times[] = { 100, 100, 100, 5, 2};
	GraphRepresentationInterface* graph = new MatrixGraphRepresentation(false, 1);
	GraphRepresentationInterface* graph2 = new MatrixGraphRepresentation(false, 1);
	GraphRepresentationInterface* graph3 = new MatrixGraphRepresentation(false, 1);
	MinimumSpanningTreeAlgoritm* mst = new MinimumSpanningTreeAlgoritm(graph);
	fstream file("result.txt", std::ios_base::app);
	fstream file2("result2.txt", std::ios_base::app);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Timer *timer = new Timer();
			Timer *timer2 = new Timer();
			graph->generateGraph(vCount[i], dens[j], 1, 99);
			for (int k = 0; k < times[i]; k++) {
				timer->startTimer();
				graph2 = mst->makeKruskalMst(graph2);
				timer->stopTimer();
				timer2->startTimer();
				graph3 = mst->makePrimMst(graph3);
				timer2->stopTimer();
				cout << vCount[i] << " - " << dens[j] << " - " << k << endl;
				timer->nextMeasure();
				timer2->nextMeasure();
			}
			file << vCount[i] << " - " << dens[j] << " - " << timer->getAvgTime() << endl;
			file2 << vCount[i] << " - " << dens[j] << " - " << timer2->getAvgTime() << endl;
			file.flush();
			file2.flush();
			delete timer;
			delete timer2;
		}
	}
	file.close();
	file2.close();
}

void test2() {
	using namespace std;
	int vCount[] = { 10, 50, 100, 500, 750 };
	float dens[] = { 0.25f, 0.5f, 0.75f, 0.99f };
	int times[] = { 100, 100, 100, 5, 2 };
	GraphRepresentationInterface* graph = new ListGraphRepresentation(true, 1);
	GraphRepresentationInterface* graph2 = new ListGraphRepresentation(true, 1);
	GraphRepresentationInterface* graph3 = new ListGraphRepresentation(true, 1);
	ShortestWayAlgoritm* mst = new ShortestWayAlgoritm(graph, 0);
	fstream file("resultS.txt", std::ios_base::out);
	fstream file2("resultS2.txt", std::ios_base::out);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Timer *timer = new Timer();
			Timer *timer2 = new Timer();
			graph->generateGraph(vCount[i], dens[j], 1, 99);
			for (int k = 0; k < times[i]; k++) {
				timer->startTimer();
				graph2 = mst->makeDikstra(graph2);
				timer->stopTimer();
				timer2->startTimer();
				graph3 = mst->makeBellman(graph3);
				timer2->stopTimer();

				timer->nextMeasure();
				timer2->nextMeasure();
			}
			file << vCount[i] << " - " << dens[j] << " - " << timer->getAvgTime();
			file2 << vCount[i] << " - " << dens[j] << " - " << timer2->getAvgTime();
			delete timer;
			delete timer2;
		}
	}
	file.close();
	file2.close();
}

int _tmain(int argc, _TCHAR* argv[]) {
	presentation();
	//test1();
	//test2();
	return 0;
}

