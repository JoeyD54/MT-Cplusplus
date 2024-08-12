//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef G_TEST_DATA_H
#define G_TEST_DATA_H

using namespace ThreadFramework;

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct G_UnitTest
{
	G_UnitTest() = delete;

	void SetTestData(const int *_x, const float *_y, char * const *_p)
	{
		assert(_x);
		assert(_y);
		assert(_p);

		this->ID = Debug::GetCurrentID();
		this->pName = (char *)Debug::GetCurrentName();
		this->x = *_x;
		this->x_addr = _x;
		this->y = *_y;
		this->y_addr = _y;
		this->p = *_p;
		this->p_addr = _p;
	}

	unsigned int ID;
	char *pName;

	int x;
	float y;
	char *p;

	const int *x_addr;
	const float *y_addr;
	const char * const * p_addr;
};

#endif

// --- End of File ---
