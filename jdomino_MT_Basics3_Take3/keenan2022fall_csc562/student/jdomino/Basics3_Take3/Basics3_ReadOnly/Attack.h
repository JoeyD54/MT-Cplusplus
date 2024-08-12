//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef ATTACK_H
#define ATTACK_H

#include "Problem_1.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Attack
{
public:
	Attack() = default;
	Attack(const Attack &) = default;
	Attack & operator =(const Attack &) = default;
	~Attack() = default;

	// function call operator
	void operator() (int val, Problem_1 &p);
};

#endif

// --- End of File ---

