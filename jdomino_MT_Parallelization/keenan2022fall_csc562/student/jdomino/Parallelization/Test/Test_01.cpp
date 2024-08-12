//-------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//-------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "List_ReadOnly.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------


using namespace std::chrono_literals;
using namespace ThreadFramework;

List *pOrigList = nullptr;
List *pNewList = nullptr;

TEST_WITH_TEARDOWN(Problem_01_Test, TestConfig::ALL)
{
#if Problem_01_Test	
	
	// -----------------------------------------------------
	// Problem 1: 
	// -----------------------------------------------------

	Trace::out("\n --- PROBLEM 1 ---\n\n");

	pOrigList = new List();
	pOrigList->CreateListForTest();
	pOrigList->Print();

	pNewList = new List();

	// Implement this "deep" copy assignment
	*pNewList = *pOrigList;

	CHECK(*pNewList == *pOrigList);

	delete pOrigList;
	pOrigList = nullptr;

	delete pNewList;
	pNewList = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(Problem_01_Test)
{
	delete pOrigList;
	delete pNewList;
}


// ---  End of File ---------------
