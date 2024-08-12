//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef K_H
#define K_H

// ----------------------------------------------------------------
// K) Spawn thread K 
//    With Member function 
//    With no parameters, no return
// 
// 1) Add a member function with three parameters to Class K
//    Modify K.h and K.pp
// 2) Add to the bottom K member function
//    Add  	K_result.SetTestData();
// 3) Spawn the thread in Unit Test
//    See AZUL_INSERT_CODE_HERE
//-----------------------------------------------------------------

class K
{
public:

	K() = default;
	K(const K &) = default;
	K& operator = (const K &) = default;
	~K() = default;

	K(int v);

	void operator() ();

	int x;
};

#endif

// --- End of File ---
