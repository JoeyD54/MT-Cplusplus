//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "F_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

F_UnitTest F_result{0};

TEST_WITH_TEARDOWN(F_Thread, TestConfig::ALL)
{
#if F_Thread
	
	Trace::out("\n");
	Trace::out("F_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// F) Write lambda_F
	//    With lambda with empty capture clause
	//    With at three parameters, no return 
	//          * value - x
	//          * reference - y
	//          * pointer = p
	// 
	// 1) Write lambda inside Unit Tests 
	//    With at three parameters 
	//          * value - x
	//          * reference - y
	//          * pointer = p
	//    Inside Lambda:
	//        Add function: 
	//            F_result.SetTestData(&x,&y,&p);  
	//            used for testing
	// 2) Spawn thread tF	
	// 
	// Hint: create a lambda, then pass it to the thread create
	//-----------------------------------------------------------------
		
	int x = 44;
	float y = 222.2f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "bird");

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create Lambda below this line, named lambda_F ----------

	auto lambda_F = [](int x, float &y, char *p)
	{
		F_result.SetTestData(&x, &y, &p);
	};

	// --- create thread below this line, named tF ----------

	std::thread tF(lambda_F, x, std::ref(y), p);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tF, "---F---");
	tF.join();

	// Verify thread
	CHECK(strcmp(F_result.pName, "---F---") == 0);
	CHECK(F_result.ID != Debug::GetCurrentID());

	CHECK(x == 44);
	CHECK(F_result.x == 44);
	CHECK(&x != nullptr);
	CHECK(F_result.x_addr != nullptr);
	CHECK(&x != F_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 222.2f) == true);
	CHECK(UnitUtility::AreEqual(F_result.y, 222.2f) == true);
	CHECK(&y != nullptr);
	CHECK(F_result.y_addr != nullptr);
	CHECK(&y == F_result.y_addr);

	CHECK(strcmp(p, "bird") == 0);
	CHECK(strcmp(F_result.p, "bird") == 0);
	CHECK(p != nullptr);
	CHECK(F_result.p != nullptr);
	CHECK(p == F_result.p);
	CHECK(F_result.p != nullptr);
	CHECK(&p != F_result.p_addr);

	delete[] p;

	Trace::out("F_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(F_Thread)
{

}

// ---  End of File ---
