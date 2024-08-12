//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Attack.h"
#include "Problem_1.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Attack::operator() (int val, Problem_1 &p)
{
	SimpleBanner b;
	
	// ------------------------------------------------------
	// Sleep added only for the Basics
	// Delay all the spawning threads to mask start up time
	// ------------------------------------------------------
	std::this_thread::sleep_for(10ms);

	const int start = val;
	const int end = val * 3;

	for (int i = start; i < end; i += val)
	{
		p.Add(i);
	}

	// ------------------------------------------------------
	// Sleep added only for the Basics
	// Delay to cover printing queue
	// ------------------------------------------------------
	std::this_thread::sleep_for(1s);

}

// --- End of File ---
