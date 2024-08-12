//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Problem_1.h"

using namespace ThreadFramework;

// -----------------------------------------------------
// Problem 1:  add lock_guard to prevent tearing prints
// -----------------------------------------------------
// Note: Do not re-arrange code
//       Record() are added to create race conditions
//------------------------------------------------------

std::mutex mtx;

void Problem_1::Add(int val)
{
	std::lock_guard<std::mutex> lockA(mtx);

	Debug::out("------\n");
	this->d.a += val;
	this->Record_A(this->d.a);

	this->d.b += val;
	this->Record_B(this->d.b);

	this->d.c += val;
	this->Record_C(this->d.c);

	this->d.d += val;
	this->Record_D(this->d.d);

	this->d.e += val;
	this->Record_E(this->d.e);
}

Problem_1::Problem_1()
	:d{0}
{

}



// --- End of File ---