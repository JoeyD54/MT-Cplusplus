//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Problem_1.h"
#include <vector>

using namespace ThreadFramework;

// -----------------------
//  DO NOT MODIFY
// -----------------------

using namespace std::chrono_literals;

void CaptureP1(int v);

void Problem_1::Record_A(int v)
{
	CaptureP1(v);
	Debug::out("d.a: %d\n", v);
	std::this_thread::sleep_for(1ms);
}

void Problem_1::Record_B(int v)
{
	CaptureP1(v);
	Debug::out("d.b: %d\n", v);
	std::this_thread::sleep_for(1ms);
}

void Problem_1::Record_C(int v)
{
	CaptureP1(v);
	Debug::out("d.c: %d\n", v);
	std::this_thread::sleep_for(1ms);
}

void Problem_1::Record_D(int v)
{
	CaptureP1(v);
	Debug::out("d.d: %d\n", v);
	std::this_thread::sleep_for(1ms);
}

void Problem_1::Record_E(int v)
{
	CaptureP1(v);
	Debug::out("d.e: %d\n", v);
	std::this_thread::sleep_for(1ms);
}

// --- End of File ---
