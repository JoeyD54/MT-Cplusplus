//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef ALPHA_DOG_H
#define ALPHA_DOG_H

class Dog;

class AlphaDog
{
public:
	AlphaDog();

	void PrintAlpha();
	void SetAlphaDog(const Dog *p);

// Static: ----------------------------
	static int SetCount;

// -------------------------------
//  Data:  (add data if desired)
// -------------------------------
	const Dog *pDog;
	std::once_flag alphaFlag;
};

#endif

// --- End of File ---
