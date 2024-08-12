//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Attack.h"
#include <vector>

using namespace ThreadFramework;
using namespace std::chrono_literals;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

std::vector<int> *pUnitTest_P1 = nullptr;// = new std::vector<int>();
std::mutex p1_mtx;

void CaptureP1(int v)
{
	std::lock_guard<std::mutex> lock(p1_mtx);
	pUnitTest_P1->push_back(v);
}


TEST_WITH_SETUP_TEARDOWN(Unit_1, TestConfig::ALL)
{
#if Unit_1

	// -----------------------------------------------------
	// Problem 1:  add lock_guard to prevent tearing prints
	// -----------------------------------------------------

	Trace::out("\n --- PROBLEM 1 ---\n\n");
	Problem_1 p;

	Attack a1;
	Attack a2;
	Attack a3;

	std::thread *t1 = new std::thread(a1, 100, std::ref(p));
	UnitTest_SetName(*t1, "A1");

	std::thread *t2 = new std::thread(a2, 1000, std::ref(p));
    UnitTest_SetName(*t2, "A2");

	std::thread *t3 = new std::thread(a3, 10000, std::ref(p));
	UnitTest_SetName(*t3, "A3");


	t1->join();
	t2->join();
	t3->join();

	for (auto it = begin(*pUnitTest_P1); it != end(*pUnitTest_P1); it++)
	{
		int a = *it++;
		int b = *it++;
		int c = *it++;
		int d = *it++;
		int e = *it;

		//Trace::out("a:%d \n", a);
		//Trace::out("b:%d \n", b);
		//Trace::out("c:%d \n", c);
		//Trace::out("d:%d \n", d);
		//Trace::out("e:%d \n", e);

		CHECK(a == b);
		CHECK(b == c);
		CHECK(c == d);
		CHECK(d == e);
		CHECK(e != 0);
	}

	Trace::out("\n");

	delete t1;
	delete t2;
	delete t3;

#endif
} TEST_END

TEST_SETUP(Unit_1)
{
	pUnitTest_P1 = new std::vector<int>();

	// Reserve - no new() created in vector inside Test
	pUnitTest_P1->reserve(64);
}

TEST_TEARDOWN(Unit_1)
{
	delete pUnitTest_P1;
}



// ---  End of File ---------------
