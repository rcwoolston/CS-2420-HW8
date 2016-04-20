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
	BFSVisit(id);
	//BFSVisit(G, s) ; // s is the source vertex ranging from 0 to n-1 
	for (int i = 0; i < n; i++) {
		if (color[i] == WHITE) {
			BFSVisit(i);
		}
	}
}

void BFSGraph::BFSVisit(int id) {
	color[id] = GRAY;
	bool found = false, done = false;

	//Save the first value, and the array to save the values;
	int *visited = new int[n];
	for (int i = 0; i < n; i++) {
		visited[i] = -1;
	}
	front = 0, rear = 0;
	Enqueue(visited, id);
	color[id] = GRAY;
	dis[id] = 0;
	int index = 1, curDistance = 1,seek = 1, printIndex=0;

	while (!done) {
		int curID = Dequeue(visited);
		if (curID == -1) {
			done = true;
			continue;
		}
		Vertex *here = adj[curID];
		while (here != NULL) {
			found = false;
			// Test to see if this node has not been visited. 
			// If it has get the next node in the linked list
			if (color[here->id] != WHITE) {
				here = here->next;
				continue;
			}
			//If Node has not been visited update its color, predesecor, and distance
			color[here->id] = GRAY;
			pre[here->id] = curID;
			dis[here->id] = dis[curID] + 1; // Get the current distance and update it by one

			// Enqueue this for later
			Enqueue(visited, here->id);

			////Test Print
			//printIndex++;
			//cout << endl << endl;
			//for (int i = 0; i <= printIndex; i++) {
			//	cout << visited[i] << "  ";
			//}

			// Get the next node in the linked list
			here = here->next;
		}
		//Since all daughters of this parent have been explored, set to black
		color[curID] = BLACK;
	}
}

void BFSGraph::Enqueue(int *queue, int save) {
	int index = 0;
	while (index < rear) {
		if (queue[index] == save) {
			return;
		}
		index++;
	}
	queue[rear] = save;
	rear++;
}
int BFSGraph::Dequeue(int *queue) {
	if (front == rear) {
		return -1;
	}
	else {
		int temp = queue[front];
		front++;
		return temp;
	}
}

void BFSGraph::PrintSP(int source, int v) {
	//Build the matrix
	BFS(source);

	//get the path back
	int distance = dis[v], maxDistance=dis[v], nextID=v, index;

	int *inOrder;
	inOrder = new int[distance];

	cout << endl << endl << "Shortest Path:  ";

	index = distance;
	while (distance != 0) {
		//cout << nextID << "  ";
		inOrder[index] = nextID;
		nextID = pre[nextID];
		distance = dis[nextID];
		index--;
	}
	inOrder[0] = source;
	while (index <= maxDistance) {
		cout << inOrder[index]<<"  ";
		index++;
	}
	cout <<"with a distance of "<<dis[v];
}