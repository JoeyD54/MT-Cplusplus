//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "B.h"
#include "B_TestData.h"

using namespace ThreadFramework;

extern B_UnitTest B_result;

// ----------------------------------------------------------------
// B) Spawn thread tB 
//    With a function 
//        With at three parameters 
//           * value - x
//           * reference - y
//           * pointer - p
// 
// 1) Create a function that takes three parameters
//    Modify B.h and B.cpp
// 2) Add to the bottom B function
//    B_result.SetTestData(&x, &y, &p);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

void Bfunc(int x, float& y, char* p)
{
	B_result.SetTestData(&x, &y, &p);
}

// --- End of File ---