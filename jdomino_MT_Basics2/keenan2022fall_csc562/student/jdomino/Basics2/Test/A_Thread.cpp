//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "A.h"
#include "A_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

A_UnitTest A_result{0};

TEST_WITH_TEARDOWN(A_Thread, TestConfig::ALL)
{
#if A_Thread
	
	Trace::out("A_Thread_Test: start\n");
	Trace::out("\n");

	// ----------------------------------------------------------------
	// A) Spawn thread tA 
	//    With a function
	//			With no parameters in the function, no return
	// 
	// 1) Create a function that takes no parameters
	//    Modify A.h and A.cpp
	// 2) Add to the bottom A function
	//    A_result.SetTestData();
	// 3) Spawn the thread in Unit Test
	//    See AZUL_INSERT_CODE_HERE
	//-----------------------------------------------------------------
	
	// --- create thread below this line, named tA ----------	

	std::thread tA(AFunc);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tA, "---A---");
	tA.join();

	// Verify thread
	CHECK(strcmp(A_result.pName, "---A---") == 0);
	CHECK(A_result.ID != Debug::GetCurrentID());
	CHECK(A_result.magic == 0x0ff374c1);

	Trace::out("A_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(A_Thread)
{

}

// ---  End of File ---
