//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "K.h"
#include "K_TestData.h"

using namespace ThreadFramework;

extern K_UnitTest K_result;

// ----------------------------------------------------------------
// K) Spawn thread K 
//    With Member function 
//    With no parameters, no return
// 
// 1) Add a member function with three parameters to Class K
//    Modify K.h and K.pp
// 2) Add to the bottom K member function
//    Add  	K_result.SetTestData();
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

K::K(int v)
	:x(v)
{
}

void K::operator()()
{
	K_result.SetTestData();
}



// --- End of File ---
