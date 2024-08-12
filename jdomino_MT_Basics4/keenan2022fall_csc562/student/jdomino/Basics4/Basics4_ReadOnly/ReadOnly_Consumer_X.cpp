//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Consumer_X.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Capture_X(unsigned short v);

Consumer_X::Consumer_X(const char *const name)
	: BannerBase(name)
{

}

void Consumer_X::Display(const SharedData &r)
{
	Debug::out("0x%x <--- \n", r.complement);
	Capture_X(r.complement);
}

// --- End of File ---
