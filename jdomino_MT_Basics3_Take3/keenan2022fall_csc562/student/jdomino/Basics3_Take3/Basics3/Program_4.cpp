//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Problem_4.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

extern bool Test4_flag;

// -----------------------------------------------------
// Problem 4:  Lock all 3 mutexes
//             Using unique_lock
//             Using adopt_lock
// -----------------------------------------------------
// Note: Do not re-arrange code 
//       Only add necessary code to complete task
//------------------------------------------------------
void Problem_4::operator()(Student4 &s0, Student4 &s1, Student4 &s2, int val)
{
	SimpleBanner b;

	// ------------------------------------------------------
	// Delay all the spawning threads to mask start up time
	// Create the collision desired for Basics
	// ------------------------------------------------------
	while(!Test4_flag)
	{
		// hold until.. released
	}
	
	std::lock(s0.mtx, s1.mtx, s2.mtx);

	std::unique_lock<std::mutex> lockA(s0.mtx, std::adopt_lock);
	std::unique_lock<std::mutex> lockB(s1.mtx, std::adopt_lock);
	std::unique_lock<std::mutex> lockC(s2.mtx, std::adopt_lock);

	s0.score += val;
	s1.score += val;
	s2.score += val;

	Debug::out("val:%d\n", val);
	Debug::out("--------\n");
	Debug::out("name(%s):%d \n", s0.GetName(), s0.score);
	Debug::out("name(%s):%d \n", s1.GetName(), s1.score);
	Debug::out("name(%s):%d \n", s2.GetName(), s2.score);
	Debug::out("--------\n");
}

// --- End of File ---
