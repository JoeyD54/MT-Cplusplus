//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Dog.h"
#include "AlphaDog.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

extern bool Test5_flag;

static const char *StringName[6]
{
	"Fido  ",
	"Snoopy",
	"Rex   ",
	"Killer",
	"Fluffy",
	"-NONE-"
};

// --------------------------------------------------------
// Problem 5:  Add call_once 
//             Insure that only one thread sets alpha dog
//             Add the flag and modify the code minimally
// --------------------------------------------------------
void Dog::operator() (Dog &pIn, AlphaDog &alpha)
{
	SimpleBanner b;

	// ------------------------------------------------------
	// Delay all the spawning threads to mask start up time
	// Create the collision desired for Basics
	// ------------------------------------------------------
	while(!Test5_flag)
	{
		// hold until.. released
	}

	Debug::out("--> SetAlpha (%p):%s\n", &pIn,	pIn.GetName());

	std::call_once(alpha.alphaFlag, &AlphaDog::SetAlphaDog, alpha, &pIn);
	alpha.PrintAlpha();
}

Dog::Dog()
:name(Name::None)
{

}

Dog::Dog(Name _name)
:name(_name)
{

}

const char *Dog::GetName() const
{
	return StringName[(int)this->name];
}

// --- End of File ---
