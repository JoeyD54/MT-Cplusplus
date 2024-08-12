//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "SimulatedMain.h"
#include <conio.h>

#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"
#include "Controller.h"
#include "ThreadCount.h"
#include "SharedData.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------
void TestInterrupt()
{
	Debug::SetCurrentName("Async_Test");
	INPUT ip;

	// Sleep to let all the threads do some work
	std::this_thread::sleep_for(5s);

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = 0x41; //<---- "A"
	ip.ki.dwFlags = 0;

	Debug::out("<--- Key Press\n");

	//Simulate pressing A on the keyboard
	SendInput(1, &ip, sizeof(INPUT));
}

TEST_WITH_SETUP_TEARDOWN(Kill_Check, TestConfig::VERSION_CHECK)
{
#if Kill_Check

	// -----------------------------------------------------
	// Launch the simulated main
	// -----------------------------------------------------
	std::thread t_UserMain(SimulatedMain);
	Debug::SetName(t_UserMain, "-sim_main-");

	// -----------------------------------------------------
	// Kill_CHECK
	// -----------------------------------------------------

	std::this_thread::sleep_for(100ms);

	//In the test function body
	std::future<void> fuInterrupter = std::async(std::launch::async,
											     &TestInterrupt);
	fuInterrupter.get();
	
	// Join
    t_UserMain.join();

	Trace::out("\n");
	std::this_thread::sleep_for(1s);

#endif
} TEST_END

TEST_SETUP(Kill_Check)
{
#if Kill_Check



#endif
}

TEST_TEARDOWN(Kill_Check)
{
#if Kill_Check



#endif
}


// ---  End of File ---------------
