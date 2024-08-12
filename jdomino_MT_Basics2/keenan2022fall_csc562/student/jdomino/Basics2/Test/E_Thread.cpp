//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "E_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

E_UnitTest E_result{0};

TEST_WITH_TEARDOWN(E_Thread, TestConfig::ALL)
{
#if E_Thread
	
	Trace::out("\n");
	Trace::out("E_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// E) Write lambda_E
	//    With lambda with empty capture clause
	//        With no input parameters, no return  
	// 
	// 1) Write lambda inside Unit Test
	//    With lambda with empty capture clause
	//        With no input parameters 
	//    Inside Lambda:
	//        Add function: 
	//            E_result.SetTestData(&x); 
	//            used for testing
	// 2) Spawn thread tE 
	// 
	// Hint: create a lambda, then pass it to the thread create
	//-----------------------------------------------------------------
	
	int x = 33;

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);

	// --- create Lambda below this line, named lambda_E ----------

	auto lambda_E = []()
	{
		int x = 777; 

		E_result.SetTestData(&x);
	};

	// --- create thread below this line, named tE ----------

	std::thread tE(lambda_E);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tE, "---E---");
	tE.join();

	// Verify thread
	CHECK(strcmp(E_result.pName, "---E---") == 0);
	CHECK(E_result.ID != Debug::GetCurrentID());
	CHECK(E_result.x == 777);
	CHECK(E_result.x_addr != nullptr);
	CHECK(x == 33);
	CHECK(&x != nullptr);
	CHECK(&x != E_result.x_addr);

	Trace::out("E_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(E_Thread)
{

}

// ---  End of File ---
