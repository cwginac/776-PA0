#include "Node.h"


Node::Node(Node* parentNode, pair <int, int> sSide, pair<int, int> oSide, bool bDirection, string sDesription)
{
	parent = parentNode;
	startingSide = sSide;
	otherSide = oSide;
	direction = bDirection;
	description = sDesription;
}

bool Node::isFinalState()
{
	pair <int, int> finalState = make_pair(0, 0);

	return (startingSide == finalState);
}

bool Node::isSafeState()
{
	bool safeState = true;

	// If missionaries are outnumbered by cannibals and there are missionaries to eat,
	// then it is not a safe state.
	if((startingSide.first < startingSide.second && startingSide.first > 0) 
		|| (otherSide.first < otherSide.second && otherSide.first > 0))
	{
		safeState = false;
	}

	return safeState;
}


void Node::makeChildren()
{
	pair <int, int> sSide = startingSide;
	pair <int, int> oSide = otherSide;

	//Move 1 Missionary
	if(direction)
	{
		sSide.first--;
		oSide.first++;
	}
	else
	{
		sSide.first++;
		oSide.first--;
	}

	//Create child if we are in a valid (not necessarily safe) configuration
	if(sSide.first > -1 && sSide.second > -1 && oSide.first > -1 && oSide.second > -1)
		children.push_back(new Node(this, sSide, oSide, !direction, "Move 1 missionary."));

	//Move 2 Missionaries
	sSide = startingSide;
	oSide = otherSide;

	if(direction)
	{
		sSide.first -= 2;
		oSide.first += 2;
	}
	else
	{
		sSide.first += 2;
		oSide.first -= 2;
	}
	//Create child if we are in a valid (not necessarily safe) configuration
	if(sSide.first > -1 && sSide.second > -1 && oSide.first > -1 && oSide.second > -1)
		children.push_back(new Node(this, sSide, oSide, !direction, "Move 2 missionaries."));

	//Move 1 Cannibal
	sSide = startingSide;
	oSide = otherSide;

	if(direction)
	{
		sSide.second--;
		oSide.second++;
	}
	else
	{
		sSide.second++;
		oSide.second--;
	}

	//Create child if we are in a valid (not necessarily safe) configuration
	if(sSide.first > -1 && sSide.second > -1 && oSide.first > -1 && oSide.second > -1)
		children.push_back(new Node(this, sSide, oSide, !direction, "Move 1 cannibal."));
	
	//Move 2 Cannibals
	sSide = startingSide;
	oSide = otherSide;

	if(direction)
	{
		sSide.second -= 2;
		oSide.second += 2;
	}
	else
	{
		sSide.second += 2;
		oSide.second -= 2;
	}

	//Create child if we are in a valid (not necessarily safe) configuration
	if(sSide.first > -1 && sSide.second > -1 && oSide.first > -1 && oSide.second > -1)
		children.push_back(new Node(this, sSide, oSide, !direction, "Move two cannibals."));

	//Move 1 of each
	sSide = startingSide;
	oSide = otherSide;

	if(direction)
	{
		sSide.first--;
		oSide.first++;
		sSide.second--;
		oSide.second++;
	}
	else
	{
		sSide.first++;
		oSide.first--;
		sSide.second++;
		oSide.second--;
	}

	//Create child if we are in a valid (not necessarily safe) configuration
	if(sSide.first > -1 && sSide.second > -1 && oSide.first > -1 && oSide.second > -1)
		children.push_back(new Node(this, sSide, oSide, !direction, "Move one of each."));
}