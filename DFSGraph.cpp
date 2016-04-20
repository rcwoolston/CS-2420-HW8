#pragma once
#include <string>
#include <iostream>
#include "DFSGraph.h"

using namespace std;

DFSGraph::DFSGraph(int n_input) {
	n = n_input;
	adj = new Vertex*[n];

	color = new colorType[n];
	pre = new int[n];

	for (int i = 0; i < n; i++) {
		adj[i] = NULL;
	}
}

void DFSGraph::setAdjLists(int *adjM) {
	for (int i = 0; i < n; i++) {
		for (int j = (n - 1); j >= 0; j--) {
			if (adjM[i*n + j] == 1) {
				Vertex *v = new Vertex(j);
				v->next = adj[i];
				adj[i] = v;
			}
		}
	}
}

void DFSGraph::printAdjLists() {
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

void DFSGraph::DFS(int id) {
	for (int i = 0; i < n; i++) {
		color[i] = WHITE2;
		pre[i] = -1;
	}

	DFSVisit(id);

	for (int i = 0; i < n; i++) {
		if (color[i] == WHITE2) {
			DFSVisit(i);
		}
	}
}

void DFSGraph::DFSVisit(int id) {
	color[id] = GRAY2;
	Vertex *v = adj[id]; 
	while (v != NULL) { 
		if (color[v->id] == WHITE2) { 
			pre[v->id] = id; 
			DFSVisit(v->id); 
		} 
		v = v->next; 
	} 
	color[id] = BLACK2; 
}

void DFSGraph::PrintReachableNodes(int source) {
	cout << " " << source << " ";
	for (int i = 0; i < n; i++) {
		if (pre[i] == source) {
			PrintReachableNodes(i);
		}
	}

	return;
}