//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef C_H
#define C_H

// ----------------------------------------------------------------
// C) Spawn thread tC 
//    With a function object (functor) 
//         With no parameters
// 
// 1) Add a function call operator to Class C.
//         Modify C.h and C.pp
// 2) Add to the bottom C function call operator
//    Add C_result.SetTestData(*this);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

class C
{
public:
	C() = default;
	C(const C &) = default;
	C & operator = (const C &) = delete;
	~C() = default;

	C(int v);
	int GetX();
	
private:
	int x;
};

void CFunc(C& inC);

#endif

// --- End of File ---
