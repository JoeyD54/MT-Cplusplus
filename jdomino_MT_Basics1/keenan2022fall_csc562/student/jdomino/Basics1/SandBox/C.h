//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef C_H
#define C_H

#include "UnitTest_Log.h"

class C
{
public:
	// ---------------------------------------------------
	// --> Implement the BIG Six
	// ---------------------------------------------------

		//Big 6
	//1 Default constructor
	C();

	//2 Copy constructor
	C(const C& in);

	//3 Assignment Operator
	C& operator = (const C& in);

	//4 Destructor
	~C();

	//5 Move Constructor
	C(C&& in) noexcept;

	//6 Assignment Move
	C& operator = (C&& in) noexcept;

	// -----------------------------------------------------
	//  Do not modify below this line
	//  used in tests
	// -----------------------------------------------------

	C(const int x, const char *pString);

	void Log(TestingLog::Type _methodName, const C &Copy_OR_Move_Argument);
	void Log(TestingLog::Type _methodName);

	static C foo();
	static void foo1(C &&p);

	// -------------------------
	//  Data
	// -------------------------
public:
	int	c0;
	char *poString;

};

#endif // A_H

// ---- End of File ----
