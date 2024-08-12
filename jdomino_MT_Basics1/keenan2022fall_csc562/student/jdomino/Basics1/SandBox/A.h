//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_H
#define A_H

#include "UnitTest_Log.h"

class A
{
public:
	// ---------------------------------------------------
	// --> Implement the BIG Six
	// ---------------------------------------------------


	// -----------------------------------------------------
	//  Do not modify below this line
	//  used in tests
	// -----------------------------------------------------

	//Big 6
	//1 Default constructor
	A();

	//2 Copy constructor
	A(const A& in);

	//3 Assignment Operator
	A& operator = (const A& in);

	//4 Destructor
	~A();

	//5 Move Constructor
	A(A&& in) noexcept;

	//6 Assignment Move
	A& operator = (A&& in) noexcept;
	

	//Specialized Constructor
	A(const int x, const int y);

	void Log(TestingLog::Type _methodName, const A& Copy_OR_Move_Argument);
	void Log(TestingLog::Type _methodName);

	static A foo();
	static void foo1(A&& p);

	// -------------------------
	//  Data
	// -------------------------
public:
	int	a0;
	int	a1;

};

#endif // A_H

// ---- End of File ----
