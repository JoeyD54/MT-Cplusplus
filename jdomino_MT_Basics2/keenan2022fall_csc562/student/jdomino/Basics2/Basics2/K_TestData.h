//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef K_TEST_DATA_H
#define K_TEST_DATA_H
		
using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct K_UnitTest
{
	void SetTestData()
	{
		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->magic = 0x98ba2b51;
	}

	unsigned int ID;
	char *pName;
	unsigned int magic;
};

#endif

// --- End of File ---

