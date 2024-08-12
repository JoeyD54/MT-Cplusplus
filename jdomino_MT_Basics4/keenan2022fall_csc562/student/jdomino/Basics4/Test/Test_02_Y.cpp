//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Producer.h"
#include "Consumer_Y.h"

#include <vector>

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#if !Problem_Y

	void Capture_Y(unsigned short )
	{
		// stubbed out - for testing settings
	}

#else

	std::vector<unsigned short> *pUnitTest_Y = nullptr;
	std::mutex Y_mtx;

	void Capture_Y(unsigned short v)
	{
		std::lock_guard<std::mutex> lock(Y_mtx);
		pUnitTest_Y->push_back(v);
	}

	unsigned short Y_answer[] =
	{
		0x5555,
		0x4444,
		0xbbbb,
		0x3333,
		0x1111,
		0xeeee,
		0x9999,
		0xcccc,
		0xdddd,
		0xaaaa,
		0x8888,
		0x7777,
		0x6666,
		0x2222,
		0x0
	};
#endif

TEST_WITH_SETUP_TEARDOWN(Problem_Y, TestConfig::ALL)
{
#if Problem_Y

	// -----------------------------------------------------
	// Problem 2: 
	// -----------------------------------------------------

	Trace::out("\n --- PROBLEM Y ---\n\n");
	
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

	Consumer_Y CA("Con_A");
	Consumer_Y CB("Con_B");
	Consumer_Y CC("Con_C");
	Consumer_Y CD("Con_D");
	Producer PA(" Prod");

	std::thread  tConsumerA(CA, std::ref(data), tToc);
	std::thread  tConsumerB(CB, std::ref(data), tToc);
	std::thread  tConsumerC(CC, std::ref(data), tToc);
	std::thread  tConsumerD(CD, std::ref(data), tToc);
	
	// Guarantee that consumer threads started BEFORE producer
	std::this_thread::sleep_for(10ms);

	std::thread  tProducer(PA, std::ref(data), tToc);

	tProducer.join();
	tConsumerA.join();
	tConsumerB.join();
	tConsumerC.join();
	tConsumerD.join();

	// Complete in time?
	auto tB = std::chrono::system_clock::now();
	CHECK( (tB - tA) < (13250ms) );

	int i = 0;
	for (auto it = begin(*pUnitTest_Y); it != end(*pUnitTest_Y); it++)
	{
		unsigned short a = *it;
		CHECK(a == Y_answer[i++]);
		//Trace::out("Test:%x \n", a);
	}


#endif
} TEST_END

TEST_SETUP(Problem_Y)
{
#if Problem_Y

	pUnitTest_Y = new std::vector<unsigned short>;
	assert(pUnitTest_Y);
	pUnitTest_Y->reserve(16);

#endif
}

TEST_TEARDOWN(Problem_Y)
{
#if Problem_Y

	delete pUnitTest_Y;

#endif
}



// ---  End of File ---------------
