#include <iostream>
#include <string>
#include <fstream>
#include "BFSGraph.h"
#include "DFSGraph.h"

using namespace std;

int main() {
	fstream bfs, dfs;
	int tempInt, tempIntSource;
	string tempString;
	BFSGraph *BFSG;
	DFSGraph *DFSG;
	bool done = false;
	char choice;

	//Open files
	bfs.open("Assign8BFSInput.txt",ios::in);
	dfs.open("Assign8DFSInput.txt",ios::in);

	// Get the number of vertices
	bfs >> tempInt;


	BFSG = new BFSGraph(tempInt);

	int *M1,size = tempInt*tempInt;
	M1 = new int[size];

	for (int i = 0; i < size; i++) {
		bfs >> tempInt;
		*(M1 + i) = tempInt;
	}

	//Generate the lists
	(*BFSG).SetAdjLists((M1));

	//Print out the just generated list
	(*BFSG).PrintAdjLists();

	(*BFSG).BFS(0);

	(*BFSG).PrintSP(0, 4);

	// DFS Section
	dfs >> tempInt;

	DFSG = new DFSGraph(tempInt);

	int *M2, size2 = tempInt*tempInt;
	M2 = new int[size2];

	for (int i = 0; i < size2; i++) {
		dfs >> tempInt;
		*(M2 + i) = tempInt;
	}

	(*DFSG).setAdjLists(M2);

	(*DFSG).printAdjLists();

	(*DFSG).DFS(0);

	(*DFSG).PrintReachableNodes(0);

	(*DFSG).DFS(4);

	(*DFSG).PrintReachableNodes(4);

	system("pause");

	dfs.close();
	bfs.close();

	// Driver code
	while (!done) {
		tempInt = -1;
		cout << endl << endl << "Main Menu" << endl;

		//Options for the menu
		cout << endl << "(B)readth first graph";
		cout << endl << "(D)epth first graph";
		cout << endl << "(E)xit";
		cout << endl << "Choice: ";
		cin >> choice;

		//cout << endl << "Enter source: ";
		//cin >> tempInt;

		choice = tolower(choice);
		cin.ignore();

		switch (choice)
		{
		case 'b': cout << endl << endl << "BFSGraph Submenu" << endl;
			cout << endl << "(P)rint adjacent lists ";
			cout << endl << "P(r)int shortest route ";
			cout << endl << "Choice: ";
			cin >> choice;

			choice = tolower(choice);

			if (choice == 'p') {
				(*BFSG).PrintAdjLists();
			}
			else if (choice == 'r') {
				cout << endl << "Enter source ";
				cin >> tempIntSource;

				cout << endl << "Enter destination ";
				cin >> tempInt;
				
				(*BFSG).BFS(tempIntSource);
				(*BFSG).PrintSP(tempIntSource, tempInt);
			}
			else {
				cout << endl << endl << "Invalid choice, returning to main menu";
			}

			break;
		case 'd':cout << endl << endl << "DFSGraph Submenu" << endl;
			cout << endl << "(P)rint adjacent lists ";
			cout << endl << "P(r)int reachable nodes ";
			cout << endl << "Choice: ";
			cin >> choice;

			choice = tolower(choice);

			if (choice == 'p') {
				(*DFSG).printAdjLists();
			}
			else if (choice == 'r') {
				cout << endl << "Enter source ";
				cin >> tempIntSource;
				(*DFSG).DFS(tempIntSource);
				cout << "Reachable nodes: ";
				(*DFSG).PrintReachableNodes(tempIntSource);
			}
			else {
				cout << endl << endl << "Invalid choice, returning to main menu";
			}
			break;
		//Exit the loop
		case 'e': cout << endl << "Exiting"; done = true;
			break;
		//Incorrect value
		default: cout << endl<<endl<<"Invalid option. Please choice B, D, or E";
			break;
		}

		
	}

	// Exit the program
	return 0;
}