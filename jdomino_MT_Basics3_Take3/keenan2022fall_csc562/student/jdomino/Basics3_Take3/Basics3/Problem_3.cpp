//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Problem_3.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

extern bool Test3_flag;

// -----------------------------------------------------
// Problem 3:  Lock all 3 mutexes
//             Using unique_lock
//             Using defer_lock
// -----------------------------------------------------
// Note: Do not re-arrange code 
//       Only add necessary code to complete task
//------------------------------------------------------
void Problem_3::operator()(Student3 &s0, Student3 &s1, Student3 &s2, int val)
{
	SimpleBanner b;

	// ------------------------------------------------------
	// Delay all the spawning threads to mask start up time
	// Create the collision desired for Basics
	// ------------------------------------------------------
	while(!Test3_flag)
	{
		// hold until.. released
	}
	
	std::unique_lock<std::mutex> lockA(s0.mtx, std::defer_lock);
	std::unique_lock<std::mutex> lockB(s1.mtx, std::defer_lock);
	std::unique_lock<std::mutex> lockC(s2.mtx, std::defer_lock);

	std::lock(lockA, lockB, lockC);


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
