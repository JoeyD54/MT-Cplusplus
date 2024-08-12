//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef I_TEST_DATA_H
#define I_TEST_DATA_H

using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct I_UnitTest
{
	void SetTestData()
	{
		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->magic = 0x67410db;
	}

	unsigned int ID;
	char *pName;
	unsigned int magic;
};

#endif

// --- End of File ---

