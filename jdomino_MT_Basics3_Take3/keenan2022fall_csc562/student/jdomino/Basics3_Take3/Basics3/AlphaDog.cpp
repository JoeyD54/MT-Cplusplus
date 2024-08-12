//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Dog.h"
#include "AlphaDog.h"

using namespace ThreadFramework;

int AlphaDog::SetCount = 0;

void AlphaDog::SetAlphaDog(const Dog *p)
{	
	// ----------------------------------------------
	// You cannot modify this method
	// ----------------------------------------------
	AlphaDog::SetCount++;

	assert(p != nullptr);
	this->pDog = p;
}

AlphaDog::AlphaDog()
	: pDog(nullptr)
{
}

void AlphaDog::PrintAlpha()
{
	Debug::out("Alpha Dog: %s SetCount:%d\n", this->pDog->GetName(), AlphaDog::SetCount);
}

// --- End of File ---
