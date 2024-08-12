//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "K.h"
#include "K_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

K_UnitTest K_result{0};

TEST_WITH_TEARDOWN(K_Thread, TestConfig::ALL)
{
#if K_Thread
	
	Trace::out("\n");
	Trace::out("J_Thread_Test: start\n");
	Trace::out("\n");

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

	K myK(654);

	// --- create thread below this line, named tK ----------
	
	std::thread tK(myK);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tK, "---K---");
	tK.join();

	// Verify thread
	CHECK(strcmp(K_result.pName, "---K---") == 0);
	CHECK(K_result.ID != Debug::GetCurrentID());
	CHECK(K_result.magic == 0x98ba2b51);

	Trace::out("K_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(K_Thread)
{

}

// ---  End of File ---
