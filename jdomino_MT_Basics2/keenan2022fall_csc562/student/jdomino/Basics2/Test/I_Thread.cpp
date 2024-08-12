//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "I.h"
#include "I_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

I_UnitTest I_result{0};

TEST_WITH_TEARDOWN(I_Thread, TestConfig::ALL)
{
#if I_Thread
	
	Trace::out("I_Thread_Test: start\n");

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

	// --- Define a function pointer and associate to I() ----------

	void(*IFuncPointer)();
	IFuncPointer = &IFunc;

	// --- create thread below this line, named tI ----------

	std::thread tI(IFuncPointer);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tI, "---I---");
	tI.join();

	// Verify thread
	CHECK(strcmp(I_result.pName, "---I---") == 0);
	CHECK(I_result.ID != Debug::GetCurrentID());
	CHECK(I_result.magic == 0x67410db);

	Trace::out("I_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(I_Thread)
{

}

// ---  End of File ---
