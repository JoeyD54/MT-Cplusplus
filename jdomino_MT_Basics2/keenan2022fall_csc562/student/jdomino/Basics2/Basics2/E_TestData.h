//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef E_TEST_DATA_H
#define E_TEST_DATA_H

using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct E_UnitTest
{
	// pass local variable x into this function
	void SetTestData(int *_x)
	{
		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->x = *_x;
		this->x_addr = _x;
	}

	unsigned int ID;
	char *pName;
	int x;
	void *x_addr;
};

#endif

// --- End of File ---
