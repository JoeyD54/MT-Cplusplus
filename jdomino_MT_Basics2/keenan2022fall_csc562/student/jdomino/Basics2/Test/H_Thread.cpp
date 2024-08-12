//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "H_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

H_UnitTest H_result{0};

TEST_WITH_TEARDOWN(H_Thread, TestConfig::ALL)
{
#if H_Thread
	
	Trace::out("\n");
	Trace::out("H_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// G) Write lambda_H
	//    With lambda copy by reference capture 
	//    With no parameters, no return
	// 
	// 1) Write lambda inside Unit Tests 
	//    With lambda copy by reference capture 
	//    With no parameters
	//    Inside Lambda:
	//        Add function: 
	//            H_result.SetTestData(&x,&y,&p);    
	//            used for testing
	// 2) Spawn thread tG
	// 
	// Hint: create a lambda, then pass it to the thread create
	//-----------------------------------------------------------------

	int x = 22;
	float y = 222.2f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "cats");

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create Lambda below this line, named lambda_H ----------

	auto lambda_H = [&]()
	{
		H_result.SetTestData(&x, &y, &p);
	};

	// --- create thread below this line, named tH ----------

	std::thread tH(lambda_H);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tH, "---H---");
	tH.join();

	// Verify thread
	CHECK(strcmp(H_result.pName, "---H---") == 0);
	CHECK(H_result.ID != Debug::GetCurrentID());

	CHECK(x == 22);
	CHECK(H_result.x == 22);
	CHECK(&x != nullptr);
	CHECK(H_result.x_addr != nullptr);
	CHECK(&x == H_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 222.2f) == true);
	CHECK(UnitUtility::AreEqual(H_result.y, 222.2f) == true);
	CHECK(&y != nullptr);
	CHECK(H_result.y_addr != nullptr);
	CHECK(&y == H_result.y_addr);

	CHECK(strcmp(p, "cats") == 0);
	CHECK(strcmp(H_result.p, "cats") == 0);
	CHECK(p != nullptr);
	CHECK(H_result.p != nullptr);
	CHECK(p == H_result.p);
	CHECK(H_result.p != nullptr);
	CHECK(&p == H_result.p_addr);

	delete[] p;

	Trace::out("H_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(H_Thread)
{

}

// ---  End of File ---
