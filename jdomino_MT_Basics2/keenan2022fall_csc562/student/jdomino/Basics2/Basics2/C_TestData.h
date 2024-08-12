//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef C_TEST_DATA_H
#define C_TEST_DATA_H

#include "C.h"

using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct C_UnitTest
{
	void SetTestData(C &r)
	{
		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->x = r.GetX();
	}

	unsigned int ID;
	char *pName;
	int x;
};

#endif

// --- End of File ---

