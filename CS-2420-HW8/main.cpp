#include <iostream>
#include <string>
#include <fstream>
#include "BFSGraph.h"
#include "DFSGraph.h"

using namespace std;

int main() {
	fstream bfs, dfs;
	int tempInt;
	string tempString;
	BFSGraph *BFSG;

	//Open files
	bfs.open("Assign8BFSInput.txt",ios::in);
	dfs.open("Assign8DFSInput.txt",ios::in);

	// Get the number of vertices
	bfs >> tempInt;


	BFSG = new BFSGraph(tempInt);

	int *adjM,size = tempInt*tempInt;
	adjM = new int[size];

	for (int i = 0; i < size; i++) {
		bfs >> tempInt;
		*(adjM + i) = tempInt;
	}

	//Generate the lists
	(*BFSG).SetAdjLists((adjM));

	//Print out the just generated list
	(*BFSG).PrintAdjLists();

	(*BFSG).BFS(0);

	(*BFSG).PrintSP(0, 4);

	system("pause");

	return 0;
}