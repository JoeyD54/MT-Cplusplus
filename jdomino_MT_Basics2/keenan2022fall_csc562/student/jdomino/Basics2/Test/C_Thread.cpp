//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "C.h"
#include "C_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

C_UnitTest C_result{0};

TEST_WITH_TEARDOWN(C_Thread, TestConfig::ALL)
{
#if C_Thread
	
	Trace::out("\n");
	Trace::out("C_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// C) Spawn thread tC 
	//    With a function object (functor) 
	//         With no parameters, no return
	// 
	// 1) Add a function call operator to Class C.
	//         Modify C.h and C.pp
	// 2) Add to the bottom C function call operator
	//    Add C_result.SetTestData(*this);
	// 3) Spawn the thread in Unit Test
	//    See AZUL_INSERT_CODE_HERE
	//-----------------------------------------------------------------

	C myC(99);  

	// --- create thread below this line, named tC ----------

	std::thread tC(CFunc, std::ref(myC));

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tC, "---C---");
	tC.join();

	// Verify thread
	CHECK(strcmp(C_result.pName, "---C---") == 0);
	CHECK(C_result.ID != Debug::GetCurrentID());
	CHECK(myC.GetX() == 99);
	CHECK(C_result.x == 99);

	Trace::out("C_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(C_Thread)
{

}

// ---  End of File ---
