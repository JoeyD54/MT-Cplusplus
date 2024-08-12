//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "J.h"
#include "J_TestData.h"

using namespace ThreadFramework;

extern J_UnitTest J_result;

// ----------------------------------------------------------------
// J) Spawn thread J
//     With function pointers
//     With at three parameters, no return
//        * value
//        * reference
//        * pointer
// 
// 1) Add a function with three parameters to Class J
//    Modify J.h and J.pp
// 2) Add to the bottom I function call operator
//    Add  	J_result.SetTestData(&x, &y, &p);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------


void JFunc(int x, float& y, char* p)
{
	J_result.SetTestData(&x, &y, &p);
}

// --- End of File ---

