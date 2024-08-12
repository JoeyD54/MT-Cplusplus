//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "L.h"
#include "L_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

L_UnitTest L_result{0};

TEST_WITH_TEARDOWN(L_Thread, TestConfig::ALL)
{
#if L_Thread
	
	Trace::out("\n");
	Trace::out("L_Thread_Test: start\n");
	Trace::out("\n");

	// ----------------------------------------------------------------
	// L) Spawn thread L 
	//    With Member function 
	//    With three parameters, no return 
	//        * value
	//        * reference
	//        * pointer
	// 
	// 1) Add a member function with three parameters to Class L
	//    Modify L.h and L.pp
	// 2) Add to the bottom L member function
	//    Add  	L_result.SetTestData(&x, &y, &p);
	// 3) Spawn the thread in Unit Test
	//    See AZUL_INSERT_CODE_HERE
	//-----------------------------------------------------------------

	L myL(654);

	int x = 88;
	float y = 888.8f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "jump");

	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- create thread below this line, named tL ----------
	
	std::thread tL(&L::foo, &myL, x, std::ref(y), p);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tL, "---L---");
	tL.join();

	// Verify thread
	CHECK(strcmp(L_result.pName, "---L---") == 0);
	CHECK(L_result.ID != Debug::GetCurrentID());

	CHECK(x == 88);
	CHECK(L_result.x == 88);
	CHECK(&x != nullptr);
	CHECK(L_result.x_addr != nullptr);
	CHECK(&x != L_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 888.8f) == true);
	CHECK(UnitUtility::AreEqual(L_result.y, 888.8f) == true);
	CHECK(&y != nullptr);
	CHECK(L_result.y_addr != nullptr);
	CHECK(&y == L_result.y_addr);

	CHECK(strcmp(p, "jump") == 0);
	CHECK(strcmp(L_result.p, "jump") == 0);
	CHECK(p != nullptr);
	CHECK(L_result.p != nullptr);
	CHECK(p == L_result.p);
	CHECK(L_result.p != nullptr);
	CHECK(&p != L_result.p_addr);

	delete[] p;

	Trace::out("L_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(L_Thread)
{

}

// ---  End of File ---
