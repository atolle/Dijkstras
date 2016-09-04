//****************************************************************************
//       CLASS:  CSCE-3110.021
//  ASSIGNMENT:  Homework 6, Program #2
//     STUDENT:  Andrew Tolle
// DESCRIPTION:  This program contains graph classes
//****************************************************************************

#include <iostream>		
#include <iomanip>		
#include <list>			
#include <string>		
#include <vector>		
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <fstream>
#include <stack>

using namespace std;

class Edge;

class Node
{

public:
	void AddEdge(Edge* e);						// Get and set functions for members
	int GetDist()		{ return distance; }
	string GetName()	{ return name; }
	Node* GetParent()	{ return parent; }
	bool Found()		{ return found; }
	vector<Edge*> GetEdges() 	{ return edges; }
	void IsFound()		{ found = true; }
	bool Heaped()		{ return heaped; }
	void IsHeaped()		{ heaped = true; }
	void SetDist(int d)	{ distance = d; }
	void SetParent(Node* p)	{ parent = p; }

	Node()
	{};

	Node(string n)	// Constructor sets parent to NULL and distance to infinity
	{
		name = n;
		found = false;
		distance = 99999999;
		parent = NULL;
		heaped = false;
	}

private:
	vector<Edge*> edges;	// Vector of node's edges
	string name;			// Name of node
	Node* parent;			// Parent of node
	int distance;			// Node's distance from start
	bool found;				// True if node has been found
	bool heaped;			// True if node has been inserted into heap


};

class Edge
{
public:
	int GetWeight()		{ return weight; }	// Get methods for members
	Node* GetNodeA()	{ return nodeA; }
	Node* GetNodeB()	{ return nodeB; }

	Edge(Node* A, Node* B, int w)	// constructor for new edge
	{
		nodeA = A;
		nodeB = B;
		weight = w;
	}

private:
	Node* nodeA;		// Pointer to node A
	Node* nodeB;		// Pointer to node B
	int weight;			// Weight of edge
};

void Node::AddEdge(Edge* e)	// Adds new edge
{
	edges.push_back(e);
}