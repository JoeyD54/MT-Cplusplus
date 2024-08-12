//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "B.h"
#include "B_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

B_UnitTest B_result{0};

TEST_WITH_TEARDOWN(B_Thread, TestConfig::ALL)
{
#if B_Thread

	Trace::out("\n");
	Trace::out("B_Thread_Test: start\n");
	Trace::out("\n");

	// ----------------------------------------------------------------
	// B) Spawn thread tB 
	//    With a function 
	//        With at three parameters, no return 
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

	int x = 5;
	float y = 33.3f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "ABCD");

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create thread below this line, named tB ----------

	std::thread tB(Bfunc, x, std::ref(y), p);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tB, "---B---");
	tB.join();

	// Verify thread
	CHECK(strcmp(B_result.pName, "---B---") == 0);
	CHECK(B_result.ID != Debug::GetCurrentID());

	CHECK(x == 5);
	CHECK(B_result.x == 5);
	CHECK(&x != nullptr);
	CHECK(B_result.x_addr != nullptr);
	CHECK(&x != B_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 33.3f) == true);
	CHECK(UnitUtility::AreEqual(B_result.y, 33.3f) == true);
	CHECK(&y != nullptr);
	CHECK(B_result.y_addr != nullptr);
	CHECK(&y == B_result.y_addr);

	CHECK(strcmp(p, "ABCD") == 0);
	CHECK(strcmp(B_result.p, "ABCD") == 0);
	CHECK(p != nullptr);
	CHECK(B_result.p != nullptr);
	CHECK(p == B_result.p);
	CHECK(B_result.p != nullptr);
	CHECK(&p != B_result.p_addr);

	delete[] p;
	Trace::out("B_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(B_Thread)
{

}

// ---  End of File ---
