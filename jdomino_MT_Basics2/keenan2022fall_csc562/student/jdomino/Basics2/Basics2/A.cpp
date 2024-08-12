//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "A.h"
#include "A_TestData.h"

using namespace ThreadFramework;

extern A_UnitTest A_result;

// ----------------------------------------------------------------
// A) Spawn thread tA 
//    With a function
//			With no parameters in the function
// 
// 1) Create a function that takes no parameters
//    Modify A.h and A.cpp
// 2) Add to the bottom A function
//    A_result.SetTestData();
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

void AFunc()
{
	A_result.SetTestData();
}

// --- End of File ---
