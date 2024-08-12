//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "D.h"

// -----------------------------------------------------
//  Do not modify below this line
//  used in tests
// -----------------------------------------------------

void D::Log(TestingLog::Type _methodName)
{
	TestingLog::Register(_methodName, this, nullptr);
}

void D::Log(TestingLog::Type _methodName, const D &Copy_OR_Move_Argument)
{
	TestingLog::Register(_methodName, this, &Copy_OR_Move_Argument);
}

D::D(const int x, const char *pString, const int y, Node *p)
:C(x,pString),d0(y),poHead(p)
{
	Log(TestingLog::SpecializedConstructor_Derived);
}

int D::privCountNodes(const Node *pHead) 
{
	const Node *pTmp = pHead;
	int count(0);

	while (pTmp != nullptr)
	{
		count++;
		pTmp = pTmp->pNext;
	}
	return count;
}

D D::foo()
{
	Node *pN0 = new Node();
	Node *pN1 = new Node();
	Node *pN2 = new Node();
	pN0->n0 = 90;
	pN1->n0 = 91;
	pN2->n0 = 92;
	pN0->pNext = pN1;
	pN1->pNext = pN2;
	pN2->pNext = nullptr;

	D tmp(61, "0x6", 66, pN0);
	return tmp;
}

void D::foo1(D &&p)
{
	//Trace::out("foo1 rvalue ref %p:\n",&p);
	//Trace::out("\tc0:%d \n", p.c0);
	//Trace::out("\tpoString:%p %s\n", p.poString, p.poString);
	//Trace::out("\td0:%d \n", p.d0);
	//Trace::out("\tpoHead:%p \n", p.poHead);
	//Trace::out("\t%d %d %d\n", p.poHead->n0, p.poHead->pNext->n0, p.poHead->pNext->pNext->n0);

	//Trace::out("\n");

	TestingLog::Add((int)p.c0); //61
	TestingLog::Add((int)p.poString[0]); //0
	TestingLog::Add((int)p.poString[1]); //x
	TestingLog::Add((int)p.poString[2]); //6
	TestingLog::Add((int)p.d0); //66
	TestingLog::Add((int)p.poHead->n0); //90
	TestingLog::Add((int)p.poHead->pNext->n0); //91
	TestingLog::Add((int)p.poHead->pNext->pNext->n0);  //92
}

// --- End of File ---
