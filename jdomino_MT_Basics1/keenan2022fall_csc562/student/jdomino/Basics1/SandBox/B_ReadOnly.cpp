//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "B.h"

// -----------------------------------------------------
//  Do not modify below this line
//  used in tests
// -----------------------------------------------------

B::B(int v0, int v1, int v2, int v3)
	: A(v0, v1),
	b0(v2),
	b1(v3)
{
	Log(TestingLog::SpecializedConstructor_Derived);
}

void B::Log(TestingLog::Type _methodName)
{
	TestingLog::Register(_methodName, this, nullptr);
}

void B::Log(TestingLog::Type _methodName, const B& Copy_OR_Move_Argument)
{
	TestingLog::Register(_methodName, this, &Copy_OR_Move_Argument);
}

void B::dump()
{
	Trace::out("\ta0:%d \n", this->a0);
	Trace::out("\ta1:%d \n", this->a1);
	Trace::out("\tb0:%d \n", this->b0);
	Trace::out("\tb1:%d \n", this->b1);
	Trace::out("\n");
}

B B::foo()
{
	B tmp(66, 77, 88, 99);
	return tmp;
}

void B::foo1(B&& p)
{
	//Trace::out("foo1 rvalue ref %p:\n",&p);
	//Trace::out("\ta0:%d \n", p.a0);
	//Trace::out("\ta1:%d \n", p.a1);
	//Trace::out("\tb0:%d \n", p.b0);
	//Trace::out("\tb1:%d \n", p.b1);
	//Trace::out("\n");

	TestingLog::Add(p.a0);
	TestingLog::Add(p.a1);
	TestingLog::Add(p.b0);
	TestingLog::Add(p.b1);
}

// --- End of File ---
