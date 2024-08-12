//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NODE_H
#define NODE_H

#include "UnitTest_Log.h"

class Node
{
public:
	// ---------------------------------------------------
	// --> Implement the BIG Six
	// ---------------------------------------------------
	Node();
	Node(const Node &tmp);
	Node &operator = (const Node &tmp);
	~Node();
	Node(Node &&tmp) noexcept;
	Node &operator = (Node &&tmp) noexcept;

	// -----------------------------------------------------
	//  Do not modify below this line
	//  used in tests
	// -----------------------------------------------------

	Node(const int x);

	void Log(TestingLog::Type _methodName, const Node &Copy_OR_Move_Argument);
	void Log(TestingLog::Type _methodName);

	// -------------------------
	//  Data
	// -------------------------
public:
	Node *pNext;
	int	n0;

};

#endif 

// ---- End of File ----
