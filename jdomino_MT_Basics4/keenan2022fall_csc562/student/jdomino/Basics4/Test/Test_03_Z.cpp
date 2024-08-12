//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Producer.h"
#include "Consumer_Z.h"

#include <vector>

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#if !Problem_Z

	void Capture_Z(unsigned short)
	{

	}

#else

	std::vector<unsigned short> *pUnitTest_Z = nullptr;
	std::mutex Z_mtx;

	void Capture_Z(unsigned short v)
	{
		std::lock_guard<std::mutex> lock(Z_mtx);
		pUnitTest_Z->push_back(v);
	}

	unsigned short Z_answer[] =
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

TEST_WITH_SETUP_TEARDOWN(Problem_Z, TestConfig::ALL)
{
#if Problem_Z

	// -----------------------------------------------------
	// Problem 3: 
	// -----------------------------------------------------

	Trace::out("\n --- PROBLEM Z ---\n\n");

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

	Consumer_Z CA("Con_A");
	Consumer_Z CB("Con_B");
	Consumer_Z CC("Con_C");
	Consumer_Z CD("Con_D");
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
	for (auto it = begin(*pUnitTest_Z); it != end(*pUnitTest_Z); it++)
	{
		unsigned short a = *it;
		CHECK(a == Z_answer[i++]);
		//Trace::out("Test:%x \n", a);
	}


#endif
} TEST_END

TEST_SETUP(Problem_Z)
{
#if Problem_Z

	pUnitTest_Z = new std::vector<unsigned short>;
	assert(pUnitTest_Z);
	pUnitTest_Z->reserve(64);

#endif
}

TEST_TEARDOWN(Problem_Z)
{
#if Problem_Z

	delete pUnitTest_Z;

#endif
}

// ---  End of File ---
