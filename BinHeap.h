//****************************************************************************
//       CLASS:  CSCE-3110.021
//  ASSIGNMENT:  Homework 6, Program #1
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program contains binary heap class
//****************************************************************************

#include "Graph.h"

class MinHeap
{
public:
	void Insert(Node *n);			// Insert Node into heap
	Node* DeleteMin();						// Pop minimum wait time
	int Size();						// Returns heap size

	MinHeap()
	{
		Node* firstNode = new Node("empty");	// Create new dummy customer for index 0
		nodes.push_back(firstNode);		// First index is saved for inserts
		heapSize = 0;						// Size initially 0
	}

private:
	int heapSize;			// Size of heap
	vector<Node*> nodes;	// Vector of Nodes used for min heap
};

void MinHeap::Insert(Node *n)
{
	heapSize++;
	nodes.push_back(n);		// Node is pushed to back of vector
	int pos = heapSize;

	n->IsHeaped();

	if (pos > 1)
	{
		while (nodes[pos / 2]->GetDist() > nodes[pos]->GetDist())	// Compare Node with parent and switch if necessary
		{
			nodes[pos] = nodes[pos / 2];
			pos /= 2;
			nodes[pos] = n;
		}
	}
}

Node* MinHeap::DeleteMin()
{
	if (heapSize > 0)	// Make sure heap has contents
	{
		Node* deleted;
		deleted = nodes[1];

		nodes[1] = nodes[heapSize];	// New min is last element
		nodes.resize(heapSize--);		// Decrease vector size
		Node* temp;
		int pos = 1;						// Position is set to frist element 

		while (pos <= heapSize / 2)			// Only iterate to last parent
		{
			if (pos * 2 <= heapSize)		// Make sure we don't go beyond end of vector
			{
				if (nodes[pos]->GetDist() > nodes[pos * 2]->GetDist())	// Swap parent and child if necessary
				{
					temp = nodes[pos];
					nodes[pos] = nodes[pos * 2];
					nodes[pos * 2] = temp;
				}
			}
			if (pos * 2 + 1 <= heapSize)	// Make sure we don't go beyond end of vector
			{
				if (nodes[pos]->GetDist() > nodes[pos * 2 + 1]->GetDist())	// Swap parent and child if necessary
				{
					temp = nodes[pos];
					nodes[pos] = nodes[pos * 2 + 1];
					nodes[pos * 2 + 1] = temp;
				}
			}
			pos++;	// Increment position
		}

		return deleted;
	}

	return NULL;
}

int MinHeap::Size()		// Return heap size
{
	return heapSize;
}