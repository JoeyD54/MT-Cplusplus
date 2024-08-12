//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "D.h"
#include "D_TestData.h"

extern D_UnitTest D_result;

using namespace ThreadFramework;

// ----------------------------------------------------------------
// D) Spawn thread tD 
//    With a function object (functor)
//    With three parameters 
//        * value - x
//        * reference - y
//        * pointer - p
// 
// 1) Add a function call operator to Class D.
//    Modify D.h and D.pp
// 2) Add to the bottom D function call operator
//    Add 	D_result.SetTestData(&x, &y, &p);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

D::D(int v)
	: a(v)
{
}


// --- End of File ---

void DFunc(int x, float& y, char* p)
{
	D_result.SetTestData(&x, &y, &p);
}
