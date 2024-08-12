//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef L_H
#define L_H

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class L
{
public:

	L() = default;
	L(const L &) = default;
	L& operator = (const L &) = default;
	~L() = default;

	L(int v);

	void foo(int a, float &b, char *c);

	int value;
};

#endif

// --- End of File ---
