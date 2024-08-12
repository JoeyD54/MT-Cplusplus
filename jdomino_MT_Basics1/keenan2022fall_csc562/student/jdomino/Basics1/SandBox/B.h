//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef B_H
#define B_H

#include "A.h"

class B : public A
{
public:
	// ---------------------------------------------------
	// --> Implement the BIG Six
	// ---------------------------------------------------

		//Big 6
	//1 Default constructor
	B();

	//2 Copy constructor
	B(const B& in);

	//3 Assignment Operator
	B& operator = (const B& in);

	//4 Destructor
	~B();

	//5 Move Constructor
	B(B&& in) noexcept;

	//6 Assignment Move
	B& operator = (B&& in) noexcept;

	// -----------------------------------------------------
	//  Do not modify below this line
	//  used in tests
	// -----------------------------------------------------

	B(int v0, int v1, int v2, int v3);

	void dump();

	static B foo();
	static void foo1( B && p);

	void Log(TestingLog::Type _methodName);
	void Log(TestingLog::Type _methodName, const B& Copy_OR_Move_Argument);

	// ---------------------
	// Data
	// ----------------------
public:
	int	b0;
	int	b1;

};


#endif // B_H

// ---- End of File ----
