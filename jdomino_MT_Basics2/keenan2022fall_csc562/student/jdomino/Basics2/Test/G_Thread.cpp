//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "G_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

G_UnitTest G_result{0};

TEST_WITH_TEARDOWN(G_Thread, TestConfig::ALL)
{
#if G_Thread
	
	Trace::out("\n");
	Trace::out("G_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// G) Write lambda_G
	//    With lambda copy by value capture
	//    With no parameters, no return
	// 
	// 1) Write lambda inside Unit Tests 
	//    With lambda copy by value capture
	//    With no parameters
	//    Inside Lambda:
	//        Add function: 
	//            G_result.SetTestData(&x,&y,&p);   
	//            used for testing
	// 2) Spawn thread tG	
	// 
	// Hint: create a lambda, then pass it to the thread create
	//-----------------------------------------------------------------

	int x = 88;
	float y = 999.9f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "pill");

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create Lambda below this line, named lambda_G ----------

	auto lambda_G = [=]()
	{
		G_result.SetTestData(&x, &y, &p);
	};

	// --- create thread below this line, named tG ----------

	std::thread tG(lambda_G);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tG, "---G---");
	tG.join();

	// Verify thread
	CHECK(strcmp(G_result.pName, "---G---") == 0);
	CHECK(G_result.ID != Debug::GetCurrentID());

	CHECK(x == 88);
	CHECK(G_result.x == 88);
	CHECK(&x != nullptr);
	CHECK(G_result.x_addr != nullptr);
	CHECK(&x != G_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 999.9f) == true);
	CHECK(UnitUtility::AreEqual(G_result.y, 999.9f) == true);
	CHECK(&y != nullptr);
	CHECK(G_result.y_addr != nullptr);
	CHECK(&y != G_result.y_addr);

	CHECK(strcmp(p, "pill") == 0);
	CHECK(strcmp(G_result.p, "pill") == 0);
	CHECK(p != nullptr);
	CHECK(G_result.p != nullptr);
	CHECK(p == G_result.p);
	CHECK(G_result.p != nullptr);
	CHECK(&p != G_result.p_addr);

	delete[] p;

	Trace::out("G_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(G_Thread)
{

}

// ---  End of File ---
