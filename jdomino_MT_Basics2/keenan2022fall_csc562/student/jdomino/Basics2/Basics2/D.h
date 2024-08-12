//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef D_H
#define D_H

// ----------------------------------------------------------------
// D) Spawn thread tD 
//    With a function object (functor)
//    With three parameters 
//        * value - x
//        * reference - y
//        * pointer - p
// 
// 1) Add a function call operator to Class D.
//    Modify D.h and D.pp
// 2) Add to the bottom D function call operator
//    Add 	D_result.SetTestData(&x, &y, &p);
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

class D
{
public:
	D() = default;
	D(const D &) = default;
	D & operator = (const D &) = delete;
	~D() = default;

	D(int v);

private:
	int a;
};

void DFunc(int x, float &y, char* p);

#endif

// --- End of File ---
