//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "C.h"
#include "C_TestData.h"

extern C_UnitTest C_result;

using namespace ThreadFramework;

// ----------------------------------------------------------------
// C) Spawn thread tC 
//    With a function object (functor) 
//         With no parameters
// 
// 1) Add a function call operator to Class C.
//         Modify C.h and C.pp
// 2) Add to the bottom C function call operator
//    Add C_result.SetTestData(*this);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

C::C(int v)
	: x(v)
{
}

int C::GetX()
{
	return this->x;
}


// --- End of File ---

void CFunc(C& inC)
{
	C_result.SetTestData(inC);
}
