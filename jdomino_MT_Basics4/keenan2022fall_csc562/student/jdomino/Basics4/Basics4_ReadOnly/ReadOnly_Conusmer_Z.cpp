//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Consumer_Z.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Capture_Z(unsigned short v);

Consumer_Z::Consumer_Z(const char *const name)
	: BannerBase(name)
{

}

void Consumer_Z::Display(const SharedData &r)
{
	Debug::out("0x%x <--- \n", r.complement);
	Capture_Z(r.complement);
}

// --- End of File ---
