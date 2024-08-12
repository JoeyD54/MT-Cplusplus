//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "L.h"
#include "L_TestData.h"

using namespace ThreadFramework;

extern L_UnitTest L_result;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

L::L(int v)
	:value(v)
{
}

void L::foo(int x, float &y, char *p)
{
	// Thread begins here
	Trace::out("\n");
	Debug::out("     (entry): L()\n");
	Debug::out("        (id): 0x%0X \n", Debug::GetCurrentID());
	Debug::out("    (thread): %s    \n", Debug::GetCurrentName());
	Debug::out(" x(%p): %d\n", &x, x);
	Debug::out(" y(%p): %f\n", &y, y);
	Debug::out(" p(%p): %p %s\n", &p, p, p);
	Debug::out("      (exit): L()\n");
	Trace::out("\n");

	// Used for Testing
	L_result.SetTestData(&x, &y, &p);
}

// --- End of File ---
