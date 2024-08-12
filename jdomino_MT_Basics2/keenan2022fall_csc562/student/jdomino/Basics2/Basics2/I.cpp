//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "I.h"
#include "I_TestData.h"

using namespace ThreadFramework;

extern I_UnitTest I_result;

// ----------------------------------------------------------------
// I) Spawn thread I 
//     With function pointers
//     With no parameters, no return
// 
// 1) Add a function with no parameters to Class I
//    Modify I.h and I.pp
// 2) Add to the bottom I function call operator
//    Add  I_result.SetTestData();
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

AZUL_INSERT_CODE_HERE

// --- End of File ---

void IFunc()
{
	I_result.SetTestData();
}
