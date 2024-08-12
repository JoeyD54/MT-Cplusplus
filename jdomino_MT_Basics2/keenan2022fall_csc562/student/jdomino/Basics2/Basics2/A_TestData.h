//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_TEST_DATA_H
#define A_TEST_DATA_H

using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct A_UnitTest
{
	void SetTestData()
	{
		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->magic = 0x0ff374c1;
	}

	unsigned int ID;
	char *pName;
	unsigned int magic;
};

#endif

// --- End of File ---

