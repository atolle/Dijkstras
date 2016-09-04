//****************************************************************************
//       CLASS:  CSCE-3110.021
//  ASSIGNMENT:  Homework 6, Program #1
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program performs Dijkstra's Algorithm.
//****************************************************************************

#include "BinHeap.h"

// Load graph nodes and edges
vector<Node*> LoadFromFile();
// Perform Dijkstra's algorithm
void Dijkstras(vector<Node*> nodes, string s);
// Find node
Node* FindNode(vector<Node*> nodes, string name);

int main()
{
	vector<Node*> nodes;
	string start;

	cout << endl << "+--------------------------------------------------+";
	cout << endl << "| This program will perform Dijkstra's algorithm   |";
	cout << endl << "| on a graph loaded from file.                     |";
	cout << endl << "+--------------------------------------------------+";

	// Populate list of nodes
	nodes = LoadFromFile();

	// User enters start node
	cout << endl << "Start node: ";
	cin >> start;

	cout << endl << "START: " << start;

	// Perform Dijkstra's
	Dijkstras(nodes, start);

	// for (int i = 0; i < nodes.size(); i++)
	// {
	// 	cout << endl << "NODE: " << nodes[i]->GetName();
	// 	cout << endl << "EDGES: ";
	// 	for (int j = 0; j < nodes[i]->GetEdges().size(); j++)
	// 	{
	// 		cout << endl << nodes[i]->GetEdges()[j]->GetNodeB()->GetName()
	// 			<< " " << nodes[i]->GetEdges()[j]->GetWeight();
	// 	}
	// }

	return 0;
}

// Load nodes and edges from file
vector<Node*> LoadFromFile()
{
	vector<Node*> nodes;
	string fileName, line, nodeA, nodeB, weight, del = " ";
	Node* A = NULL;
	Node* B = NULL;
	ifstream fs;
	int cnt = 0;
	size_t pos = 0;

	do   // Loop until user enters valid filename
	{
		cout << endl << "Enter filename: ";
		cin >> fileName;
		fs.open(fileName.c_str());

		if (!fs.is_open())
		{
			cout << "Invalid filename: " << fileName << endl;
		}
	} while (!fs.is_open());

	// Push numbers into heap
	while (!fs.eof())
	{
		cnt = 0;
		getline(fs, line);
		if (line != "")		// Skips extra lines in file
		{
			if (line.find(del) == std::string::npos)	// Everything without spaces are nodes
			{
				nodes.push_back(new Node(line));
			}
			else
			{
				while ((pos = line.find(del)) != std::string::npos)	// Now we are to the edges
				{													// Format: <node> space <node> space <weight>
					nodeA = line.substr(0, pos);
					line.erase(0, pos + del.size());

					nodeB = line.substr(0, pos);
					line.erase(0, pos + del.size());

					weight = line;
				}

				A = FindNode(nodes, nodeA);
				B = FindNode(nodes, nodeB);

				if (A != NULL && B != NULL)
				{
					// Create new edge
					A->AddEdge(new Edge(A, B, atoi(weight.c_str())));
					// NULL A and B for next iteration
					A = NULL;
					B = NULL;
				}
			}
		}
	}

	fs.close();

	return nodes;
}

// Perform Dijkstra's algorithm
void Dijkstras(vector<Node*> nodes, string s)
{
	Node* currNode = NULL;
	Node* adjNode = NULL;
	Node* start = FindNode(nodes, s);
	stack<Node*> path;

	if (start == NULL)
	{
		cout << endl << "ERROR: NODE NOT FOUND" << endl;
		return;
	}

	// Start node's distance is 0
	start->SetDist(0);

	// Make new heap
	MinHeap heap;

	// Insert start node into heap
	heap.Insert(start);

	do	// Continue until we've unloaded heap, which means we've processed all nodes
	{
		// Current node is root of heap
		currNode = heap.DeleteMin();

		if (currNode != NULL)
		{	
			// Current node is set to found
			currNode->IsFound();

			// Iterate through its edges
			for (int i = 0; i < currNode->GetEdges().size(); i++)
			{	
				// If adjacent node is not found, then compare distance 
				if (currNode->GetEdges()[i]->GetNodeB()->Found() == false)
				{
					adjNode = currNode->GetEdges()[i]->GetNodeB();

					// Change distance if current distance is greater than current node + edge weight
					if (adjNode->GetDist() > currNode->GetDist() + currNode->GetEdges()[i]->GetWeight())
					{
						adjNode->SetDist(currNode->GetDist() + currNode->GetEdges()[i]->GetWeight());
						adjNode->SetParent(currNode);
					}
					// If node is not in heap, insert
					if (currNode->GetEdges()[i]->GetNodeB()->Heaped() == false)
					{
						heap.Insert(adjNode);
					}
				}
			}
		}
	} while (heap.Size() > 0 && currNode != NULL);

	// Print results
	cout << endl << "+-----------------------------------------------+";
	cout << endl << "|\tNode\t|\tDv\t|\tPv\t|";
	cout << endl << "|-----------------------------------------------|";

	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetParent() != NULL)
			cout << endl << "|\t" << nodes[i]->GetName() << "\t|\t" << nodes[i]->GetDist() << "\t|\t" << nodes[i]->GetParent()->GetName() << "\t|";
		else if (nodes[i]->GetParent() == NULL && nodes[i]->GetDist() == 99999999)
			cout << endl << "|\t" << nodes[i]->GetName() << "\t|\tINF\t|\t\t|";
		else
			cout << endl << "|\t" << nodes[i]->GetName() << "\t|\t" << nodes[i]->GetDist() << "\t|\t0\t|";
	}

	cout << endl << "+-----------------------------------------------+" << endl;
}

Node* FindNode(vector<Node*> nodes, string name)
{
	// Find node in vector and return pointer
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetName() == name)
			return nodes[i];
	}

	return NULL;
}