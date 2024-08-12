//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Consumer_Y.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Capture_Y(unsigned short v);

Consumer_Y::Consumer_Y(const char *const name)
	: BannerBase(name)
{

}

void Consumer_Y::Display(const SharedData &r)
{
	Debug::out("0x%x <--- \n", r.complement);
	Capture_Y(r.complement);
}

// --- End of File ---
