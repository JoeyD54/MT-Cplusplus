//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NODE_H
#define NODE_H

// -----------------------------------------
//     DO NOT MODIFY THIS FILE
// -----------------------------------------

struct Node
{
public:
	Node();
	Node(const Node &) = delete;
	Node &operator = (const Node &) = delete;
	~Node() = default;

	void Print() const;

public:
	// Data: 
	std::string element;
	Node *pNext;
	Node *pRand;
};

#endif

// --- End of File ---
