//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "J.h"
#include "J_TestData.h"

using namespace ThreadFramework;

//-------------------------------------------
//  ---> Follow the instruction below <---
//-------------------------------------------

J_UnitTest J_result{0};

TEST_WITH_TEARDOWN(J_Thread, TestConfig::ALL)
{
#if J_Thread
	
	Trace::out("\n");
	Trace::out("J_Thread_Test: start\n");
	Trace::out("\n");

	// ----------------------------------------------------------------
	// J) Spawn thread J
	//     With function pointers
	//     With at three parameters, no return
	//        * value
	//        * reference
	//        * pointer
	// 
	// 1) Add a function with three parameters to Class J
	//    Modify J.h and J.pp
	// 2) Add to the bottom I function call operator
	//    Add  	J_result.SetTestData(&x, &y, &p);
	// 3) Spawn the thread in Unit Test
	//    See AZUL_INSERT_CODE_HERE
	//-----------------------------------------------------------------

	int x = 33;
	float y = 333.3f;
	char *p = new char[5];
	assert(p != nullptr);
	memset(p, 0x0, 5);
	strcpy_s(p, 5, "dogs");

	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);

	// --- Define a function pointer and associate to J() ----------

	void(*JFuncPointer)(int, float &, char*);
	JFuncPointer = &JFunc;

		// --- create thread below this line, named tJ ----------

		std::thread tJ(JFuncPointer, x, std::ref(y), p);

	// --- Do NOT modify below this line ----------

	UnitTest_SetName(tJ, "---J---");
	tJ.join();

	// Verify thread
	CHECK(strcmp(J_result.pName, "---J---") == 0);
	CHECK(J_result.ID != Debug::GetCurrentID());

	CHECK(x == 33);
	CHECK(J_result.x == 33);
	CHECK(&x != nullptr);
	CHECK(J_result.x_addr != nullptr);
	CHECK(&x != J_result.x_addr);

	CHECK(UnitUtility::AreEqual(y, 333.3f) == true);
	CHECK(UnitUtility::AreEqual(J_result.y, 333.3f) == true);
	CHECK(&y != nullptr);
	CHECK(J_result.y_addr != nullptr);
	CHECK(&y == J_result.y_addr);

	CHECK(strcmp(p, "dogs") == 0);
	CHECK(strcmp(J_result.p, "dogs") == 0);
	CHECK(p != nullptr);
	CHECK(J_result.p != nullptr);
	CHECK(p == J_result.p);
	CHECK(J_result.p != nullptr);
	CHECK(&p != J_result.p_addr);

	delete[] p;

	Trace::out("J_Thread_Test: end\n");
	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(J_Thread)
{

}

// ---  End of File ---
