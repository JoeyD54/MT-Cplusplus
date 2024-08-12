//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef PROBLEM_1_H
#define PROBLEM_1_H

class Problem_1
{
public:
	struct Data
	{
		int a;
		int b;
		int c;
		int d;
		int e;
	};

public:
// --------------------------------
//  Big four:
// --------------------------------
	Problem_1();
	Problem_1(const Problem_1 &) = default;
	Problem_1 & operator = (const Problem_1 &) = default;
	~Problem_1() = default;

// Used in Attack class
	void Add(int val);

// ----------------------------------
//  Do not modify: 
//     Used for race conditions
//     Used in Unit Tests
// ----------------------------------
private:
	void Record_A(int v);
	void Record_B(int v);
	void Record_C(int v);
	void Record_D(int v);
	void Record_E(int v);

// -------------------------------
//  Data:  (add data if desired)
// -------------------------------
public:
	Data		d;

};

#endif

// --- End of File ---
