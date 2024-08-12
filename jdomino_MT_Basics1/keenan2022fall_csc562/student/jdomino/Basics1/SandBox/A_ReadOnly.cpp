//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "A.h"

// -----------------------------------------------------
//  Do not modify below this line
//  used in tests
// -----------------------------------------------------

A::A(const int x, const int y)
	: a0(x),
	a1(y)
{
	Log(TestingLog::SpecializedConstructor_Base);
}

void A::Log(TestingLog::Type _methodName)
{
	TestingLog::Register(_methodName, this, nullptr);
}

void A::Log(TestingLog::Type _methodName, const A& Copy_OR_Move_Argument)
{
	TestingLog::Register(_methodName, this, &Copy_OR_Move_Argument);
}

A A::foo()
{
	A tmp(66, 77);
	return tmp;
}

void A::foo1(A&& p)
{
	//Trace::out("foo1 rvalue ref %p:\n",&p);
	//Trace::out("\ta0:%d \n", p.a0);
	//Trace::out("\ta1:%d \n", p.a1);
	//Trace::out("\n");

	TestingLog::Add(p.a0);
	TestingLog::Add(p.a1);
}

// --- End of File ---
