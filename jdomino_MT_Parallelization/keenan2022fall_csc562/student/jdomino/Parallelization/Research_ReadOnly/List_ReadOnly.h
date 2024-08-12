//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef LIST_H
#define LIST_H

#include "Node_ReadOnly.h"

// -----------------------------------------
//     DO NOT MODIFY THIS FILE
// -----------------------------------------

class List
{
public:
	static const int NodeCount = 500;

public:
	List();	
	List(const List &) = delete;
	~List();

	// Implement this function!
	List &operator = (const List &);

	void CreateListForTest();
	void Print() const;
	bool operator==( const List &other) const;

private:
	static bool Once;
	Node *poHead;
};

#endif

// --- End of File ---
