//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Problem_4.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

bool Test4_flag = false;

TEST_WITH_TEARDOWN(Unit_4, TestConfig::ALL)
{
#if Unit_4

	// -----------------------------------------------------
	// Problem 4:  Lock all 3 mutexes
	//             Using unique_lock
	//             Using adopt_lock
	// -----------------------------------------------------
	
	Trace::out("\n --- PROBLEM 4 ---\n\n");
	
	Problem_4 p;
	
	Student4 sA(Student4::Name::Lisa, 33);
	Student4 sB(Student4::Name::Jay, 555);
	Student4 sC(Student4::Name::Mike, 4444);

	Trace::out("name(%s):%d \n", sA.GetName(), sA.score);
	Trace::out("name(%s):%d \n", sB.GetName(), sB.score);
	Trace::out("name(%s):%d \n", sC.GetName(), sC.score);
	Trace::out("\n");
	
	std::thread *t1 = new std::thread(p, std::ref(sA), std::ref(sB), std::ref(sC), 15);
	UnitTest_SetName(*t1, "T1");

	std::thread *t2 = new std::thread(p, std::ref(sB), std::ref(sC), std::ref(sA), 10);
	UnitTest_SetName(*t2, "T2");

	std::thread *t3 = new std::thread(p, std::ref(sC), std::ref(sA), std::ref(sB), 20);
	UnitTest_SetName(*t3, "T3");

	std::thread *t4 = new std::thread(p, std::ref(sB), std::ref(sA), std::ref(sC), 25);
	UnitTest_SetName(*t4, "T4");

	std::thread *t5 = new std::thread(p, std::ref(sA), std::ref(sC), std::ref(sB), 30);
	UnitTest_SetName(*t5, "T5");

	std::thread *t6 = new std::thread(p, std::ref(sC), std::ref(sB), std::ref(sA), 10);
	UnitTest_SetName(*t6, "T6");

	std::this_thread::sleep_for(1s);
	Test4_flag = true;

	int A, B, C;
	int dA, dB, dC;

	A = sA.score;
	B = sB.score;
	C = sB.score;

	t1->join();

	dA = sA.score - A;
	dB = sB.score - B;
	dC = sB.score - C;

	CHECK(dA == dB);
	CHECK(dA == dC);

	t2->join();

	dA = sA.score - A;
	dB = sB.score - B;
	dC = sB.score - C;

	CHECK(dA == dB);
	CHECK(dA == dC);

	t3->join();

	dA = sA.score - A;
	dB = sB.score - B;
	dC = sB.score - C;

	CHECK(dA == dB);
	CHECK(dA == dC);

	t4->join();

	dA = sA.score - A;
	dB = sB.score - B;
	dC = sB.score - C;

	CHECK(dA == dB);
	CHECK(dA == dC);

	t5->join();

	dA = sA.score - A;
	dB = sB.score - B;
	dC = sB.score - C;

	CHECK(dA == dB);
	CHECK(dA == dC);

	t6->join();
	
	CHECK(sA.score == 143);
	CHECK(sB.score == 665);
	CHECK(sC.score == 4554);

	Trace::out("\n");

	delete t1;
	delete t2;
	delete t3;
	delete t4;
	delete t5;
	delete t6;

#endif
} TEST_END

TEST_TEARDOWN(Unit_4)
{
	
}

// ---  End of File ---
