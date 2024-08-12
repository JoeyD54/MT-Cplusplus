//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Consumer_W.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Capture_W(unsigned short v);

Consumer_W::Consumer_W(const char *const name)
	: BannerBase(name)
{

}

void Consumer_W::Display(const SharedData &r)
{
	Debug::out("0x%x <--- \n", r.complement);
	Capture_W(r.complement);
}

// --- End of File ---
