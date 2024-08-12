//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "D.h"
#include "D_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

D_UnitTest D_result{0};

TEST_WITH_TEARDOWN(D_Thread, TestConfig::ALL)
{
#if D_Thread
	
	Trace::out("\n");
	Trace::out("D_Thread_Test: start\n");

	// ----------------------------------------------------------------
	// D) Spawn thread tD 
	//    With a function object (functor)
	//    With three parameters, no return 
	//        * value - x
	//        * reference - y
	//        * pointer - p
	// 
	// 1) Add a function call operator to Class D.
	//    Modify D.h and D.pp
	// 2) Add to the bottom D function call operator
	//    Add 	D_result.SetTestData(&x, &y, &p);
	// 3) Spawn the thread in Unit Test
	//    See AZUL_INSERT_CODE_HERE
	//-----------------------------------------------------------------

	D myD(33);

	int x = 55;
	float y = 111.1f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "rick");

	Trace::out("\n");
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create thread below this line, named tD ----------

	std::thread tD(DFunc, x, std::ref(y), p);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tD, "---D---");
	tD.join();

	// Verify thread
	// Verify thread
	CHECK(strcmp(D_result.pName, "---D---") == 0);
	CHECK(D_result.ID != Debug::GetCurrentID());

	CHECK(x == 55);
	CHECK(D_result.x == 55);
	CHECK(&x != nullptr);
	CHECK(D_result.x_addr != nullptr);
	CHECK(&x != D_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 111.1f) == true);
	CHECK(UnitUtility::AreEqual(D_result.y, 111.1f) == true);
	CHECK(&y != nullptr);
	CHECK(D_result.y_addr != nullptr);
	CHECK(&y == D_result.y_addr);

	CHECK(strcmp(p, "rick") == 0);
	CHECK(strcmp(D_result.p, "rick") == 0);
	CHECK(p != nullptr);
	CHECK(D_result.p != nullptr);
	CHECK(p == D_result.p);
	CHECK(D_result.p != nullptr);
	CHECK(&p != D_result.p_addr);

	delete[] p;

	Trace::out("D_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(D_Thread)
{

}

// ---  End of File ---
