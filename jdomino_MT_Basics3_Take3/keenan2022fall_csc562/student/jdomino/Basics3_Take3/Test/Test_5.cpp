//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Dog.h"
#include "AlphaDog.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

bool Test5_flag = false;

TEST_WITH_TEARDOWN(Unit_5, TestConfig::ALL)
{
#if Unit_5

	// --------------------------------------------------------
	// Problem 5:  Add call_once 
	//             Insure that only one thread sets alpha dog
	//             Add the flag and modify the code minimally
	// --------------------------------------------------------

	Trace::out("\n --- PROBLEM 5 ---\n\n");

	AlphaDog alpha;

	Dog dA(Dog::Name::Snoopy);
	Dog dB(Dog::Name::Fido);
	Dog dC(Dog::Name::Fluffy);
	Dog dD(Dog::Name::Rex);
	Dog dE(Dog::Name::Killer);

	std::thread *t1 = new std::thread(dA, std::ref(dA), std::ref(alpha));
	UnitTest_SetName(*t1, "T1");

	std::thread *t2 = new std::thread(dB, std::ref(dB), std::ref(alpha));
	UnitTest_SetName(*t2, "T2");

	std::thread *t3 = new std::thread(dC, std::ref(dC), std::ref(alpha));
	UnitTest_SetName(*t3, "T3");

	std::thread *t4 = new std::thread(dD, std::ref(dD), std::ref(alpha));
	UnitTest_SetName(*t4, "T4");

	std::thread *t5 = new std::thread(dE, std::ref(dE), std::ref(alpha));
	UnitTest_SetName(*t5, "T5");

	std::this_thread::sleep_for(1s);
	Test5_flag = true;

	t1->join();
	t2->join();
	t3->join();
	t4->join();
	t5->join();

	Trace::out("\n");
	alpha.PrintAlpha();
	Trace::out("\n");

	CHECK(AlphaDog::SetCount == 1);

	delete t1;
	delete t2;
	delete t3;
	delete t4;
	delete t5;

#endif
} TEST_END

TEST_TEARDOWN(Unit_5)
{
	
}


// ---  End of File ---
