//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "C.h"

// -----------------------------------------------------
//  Do not modify below this line
//  used in tests
// -----------------------------------------------------

C::C(const int x, const char *pString)
	:c0(x)
{
	assert(pString);
	size_t size = strlen(pString) + 1;
	this->poString = new char[size]();
	memcpy_s(this->poString, size, pString, size);

	Log(TestingLog::SpecializedConstructor_Base);
}

void C::Log(TestingLog::Type _methodName)
{
	TestingLog::Register(_methodName, this, nullptr);
}

void C::Log(TestingLog::Type _methodName, const C &Copy_OR_Move_Argument)
{
	TestingLog::Register(_methodName, this, &Copy_OR_Move_Argument);
}

C C::foo()
{
	C tmp(66, "0x6");
	return tmp;
}

void C::foo1(C &&p)
{
	//Trace::out("foo1 rvalue ref %p:\n",&p);
	//Trace::out("\tc0:%d \n", p.c0);
	//Trace::out("\tpoString:%p %s\n", p.poString,p.poString);
	//Trace::out("\n");

	TestingLog::Add(p.c0);
	TestingLog::Add((int)p.poString[0]); //0
	TestingLog::Add((int)p.poString[1]); //x
	TestingLog::Add((int)p.poString[2]); //6
}

// --- End of File ---
