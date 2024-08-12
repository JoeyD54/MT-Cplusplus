//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Producer.h"
#include "Consumer_W.h"

#include <vector>

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#if !Problem_W

	void Capture_W(unsigned short)
	{

	}

#else

	std::vector<unsigned short> *pUnitTest_W = nullptr;
	std::mutex W_mtx;

	void Capture_W(unsigned short v)
	{
		std::lock_guard<std::mutex> lock(W_mtx);
		pUnitTest_W->push_back(v);
	}

	unsigned short W_answer[] =
	{
		0x5555,
		0x5555,
		0x5555,
		0x5555,
		0x4444,
		0x4444,
		0x4444,
		0x4444,
		0xbbbb,
		0xbbbb,
		0xbbbb,
		0xbbbb,
		0x3333,
		0x3333,
		0x3333,
		0x3333,
		0x1111,
		0x1111,
		0x1111,
		0x1111,
		0xeeee,
		0xeeee,
		0xeeee,
		0xeeee,
		0x9999,
		0x9999,
		0x9999,
		0x9999,
		0xcccc,
		0xcccc,
		0xcccc,
		0xcccc,
		0xdddd,
		0xdddd,
		0xdddd,
		0xdddd,
		0xaaaa,
		0xaaaa,
		0xaaaa,
		0xaaaa,
		0x8888,
		0x8888,
		0x8888,
		0x8888,
		0x7777,
		0x7777,
		0x7777,
		0x7777,
		0x6666,
		0x6666,
		0x6666,
		0x6666,
		0x2222,
		0x2222,
		0x2222,
		0x2222,
		0x0,
		0x0,
		0x0,
		0x0
	};
#endif

TEST_WITH_SETUP_TEARDOWN(Problem_W, TestConfig::ALL)
{
#if Problem_W

	// -----------------------------------------------------
	// Problem 4: 
	// -----------------------------------------------------

	Trace::out("\n --- PROBLEM W ---\n\n");

	START_BANNER_MAIN("main");

	//---------------------------------------------------------------------------------------------------------
	// Launch a Thread
	//---------------------------------------------------------------------------------------------------------

	// SharedData
	SharedData data;

	std::chrono::system_clock::time_point tTic = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point tToc = tTic + 13s;

	// Create a thread...
	auto tA = tTic;

	Consumer_W CA("Con_A");
	Consumer_W CB("Con_B");
	Consumer_W CC("Con_C");
	Consumer_W CD("Con_D");
	Producer PA(" Prod");

	std::thread  tConsumerA(CA, std::ref(data), tToc);
	std::thread  tConsumerB(CB, std::ref(data), tToc);
	std::thread  tConsumerC(CC, std::ref(data), tToc);
	std::thread  tConsumerD(CD, std::ref(data), tToc);

	// Guarantee that consumer threads started BEFORE producer
	std::this_thread::sleep_for(10ms);

	std::thread  tProducer(PA, std::ref(data), tToc, true);

	tProducer.join();
	tConsumerA.join();
	tConsumerB.join();
	tConsumerC.join();
	tConsumerD.join();

	// Complete in time?
	auto tB = std::chrono::system_clock::now();
	CHECK((tB - tA) < (13250ms));

	int i = 0;
	for (auto it = begin(*pUnitTest_W); it != end(*pUnitTest_W); it++)
	{
		unsigned short a = *it;
		CHECK(a == W_answer[i++]);
		//Trace::out("Test:%x \n", a);
	}

#endif
} TEST_END

TEST_SETUP(Problem_W)
{
#if Problem_W

	pUnitTest_W = new std::vector<unsigned short>;
	assert(pUnitTest_W);
	pUnitTest_W->reserve(64);

#endif
}

TEST_TEARDOWN(Problem_W)
{
#if Problem_W

	delete pUnitTest_W;

#endif
}

// ---  End of File ---
