#include <string>
#include "BFSGraph.h"

using namespace std;

BFSGraph::BFSGraph(int n_input) {
	n = n_input;
	adj = new Vertex* [n];

	color = new colorType[n];
	dis = new int[n];
	pre = new int[n];

	for (int i = 0; i < n; i++) {
		adj[i] = NULL;
	}
}

void BFSGraph::SetAdjLists(int *adjM) {
	for (int i = 0; i < n; i++) {
		for (int j = (n-1); j >= 0; j--) {
			if (adjM[i*n + j]==1) {
				Vertex *v = new Vertex(j);
				v->next = adj[i];
				adj[i] = v;
			}
		}
	}
}

void BFSGraph::PrintAdjLists() {
	for (int i = 0; i < n; i++) {
		cout << "Node: " << i << "  ";
		Vertex *here = adj[i];
		while (here != NULL) {
			cout << "Value: " << here->id << "  ";
			here = here->next;
		}
		cout << endl;
	}
}

void BFSGraph::BFS(int id) {

	for (int i = 0; i < n; i++) {
		color[i] = WHITE;
		dis[i] = -1;
		pre[i] = -1;
	}
	color[0] = GRAY;
	BFSVisit(id);
	//BFSVisit(G, s) ; // s is the source vertex ranging from 0 to n-1 
	//for (int j = 0;){ 
	//	if (color[i] == WHITE) BFSVisit(G, i); 
	//} // the red part is for visiting vertices that cannot be reached from s 
}

void BFSGraph::BFSVisit(int id) {
	color[id] = GRAY;
	bool found = false, done = false;

	//Save the first value, and the array to save the values;
	int *visted = new int[n];
	for (int i = 0; i < n; i++) {
		visted[i] = -1;
	}
	visted[0] = id;
	dis[id] = 0;
	int index = 1, curDistance = 1, curID = id, seek = 1;

	while (visted[(n - 1)] == -1) {
		Vertex *here = adj[curID];
		while (here != NULL) {
			found = false;
			for (int i = (index-1); i >= 0; i--) {
				if (here->id == visted[i]) {
					found = true;
					break;
				}
			}
			if (!found) {
				visted[index] = here->id;
				color[here->id] = GRAY;
				pre[here->id] = curID;
				dis[here->id] = curDistance;
				index++;
			}
			here = here->next;
		}
		color[curID] = BLACK;
		cout << endl << endl << "Current: ";
		for (int i = 0; i <index; i++) {
			cout << visted[i]<< "  ";
		}
		if (visted[(n - 1)] == -1) {
			curID = visted[seek];
			seek++;
			curDistance = dis[curID] + 1;
		}
	}
}
void BFSGraph::PrintSP(int source, int v) {
	//Build the matrix
	BFS(source);

	//get the path back
	int distance = dis[v], nextID=v;

	cout << endl << endl << "Shortest Path:  ";

	while (distance != 0) {
		cout << nextID << "  ";
		nextID = pre[nextID];
		distance = dis[nextID];
	}
	cout << nextID << "  ";
}