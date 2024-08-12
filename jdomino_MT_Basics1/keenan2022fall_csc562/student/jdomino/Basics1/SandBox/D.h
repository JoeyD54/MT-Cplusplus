//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef D_H
#define D_H

#include "UnitTest_Log.h"
#include "Node.h"
#include "C.h"

class D : public C
{
public:
	// ---------------------------------------------------
	// --> Implement the BIG Six
	// ---------------------------------------------------

		//Big 6
	//1 Default constructor
	D();

	//2 Copy constructor
	D(const D& in);

	//3 Assignment Operator
	D& operator = (const D& in);

	//4 Destructor
	~D();

	//5 Move Constructor
	D(D&& in) noexcept;

	//6 Assignment Move
	D& operator = (D&& in) noexcept;


	// -----------------------------------------------------
	//  Do not modify below this line
	//  used in tests
	// -----------------------------------------------------

	D(const int x, const char *pString, const int y, Node *p);

	void Log(TestingLog::Type _methodName, const D &Copy_OR_Move_Argument);
	void Log(TestingLog::Type _methodName);

	static int privCountNodes(const Node *pHead);

	static D foo();
	static void foo1(D &&p);

private:
	void privAdd(Node *const pNode);

	// -------------------------
	//  Data
	// -------------------------
public:
	int	d0;
	Node *poHead;

};

#endif // D_H

// ---- End of File ----
