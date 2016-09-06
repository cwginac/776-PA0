#include <iostream>
#include <queue>
#include "Node.h"

using namespace std;


int main ()
{
	// Ask user for how many missionaries and cannibals there are
	int numberOfMC = 0;
	cout << "Please enter how many missionaries and cannibals there are (enter one number for both):";
	cin >> numberOfMC;

	// Flag to determine what direction the boat is going in
	// true = to other side, false = back to starting side
	bool direction = true;

	// bool to break out of while loop below
	bool foundFinalState = false;

	// Queue of nodes to check/expand
	queue<Node*> toCheck;

	// Create root node and add it to the queue
	Node* root = new Node(NULL, make_pair(numberOfMC, numberOfMC), make_pair(0,0), true, "Starting point");
	toCheck.push(root);

	// pointer to current node (so we don't mess with the tree)
	Node* currentNode = NULL;

	// Breadth First Search
	while(toCheck.size() > 0 && !foundFinalState)
	{
		// Get the next node to check
		currentNode = toCheck.front();
		toCheck.pop();

		// Check for goal state
		if(currentNode->isFinalState())
		{
			foundFinalState = true;
		}
		// Make sure we want to continue down this branch of the tree
		else if(currentNode->isSafeState())
		{
			// Expand this node, and add it's children to the end of the queue.
			currentNode->makeChildren();
			for(int i = 0; i < currentNode->children.size(); i++)
			{
				toCheck.push(currentNode->children[i]);
			}
		}
	}

	// Let the user know we didn't find a path to the goals
	if (!foundFinalState)
	{
		cout << "Did not find a way to get everybody over safely." << endl;
	}

	// We should have found the optimal path now. Print out.
	while (currentNode != NULL && foundFinalState)
	{
		cout << "-----------------------------" << endl;
		if(!currentNode->direction)
			cout << "To other side." << endl;
		else
			cout << "To starting side." << endl;

		cout << currentNode->description.c_str() << endl;

		cout << "Starting Side: " << currentNode->startingSide.first << ", " << currentNode->startingSide.second << endl;
		cout << "Other Side: " << currentNode->otherSide.first << ", " << currentNode->otherSide.second << endl;

		currentNode = currentNode->parent;
	}

	return 0;
}
