//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "UnitTest_Log.h"

TestingLog *TestingLog::poInstance(nullptr);

void TestingLog::Create()
{
	assert(TestingLog::poInstance == nullptr);

	TestingLog *pInstance;
	pInstance = TestingLog::privGetInstance();
}

void TestingLog::Destroy()
{
	if(TestingLog::poInstance != nullptr)
	{
		TestingLog *pInstance;
		pInstance = TestingLog::privGetInstance();

		delete pInstance;
		TestingLog::poInstance = nullptr;
	}
}

void TestingLog::Register(TestingLog::Type n, const void* p,const void *s)
{
	switch (n)
	{
	case Type::DefaultConstructor_Base:
		Trace::out("\t1111 Base(default constructor)%p \n", p);
		TestingLog::Add(1111);
		break;

	case Type::CopyConstructor_Base:
		Trace::out("\t1122 Base(copy constructor)%p <- %p \n",p, s);
		TestingLog::Add(1122);
		break;

	case Type::AssignmentOperator_Base:
		Trace::out("\t1133 tBase(assignment operator)%p <- %p \n",p,s);
		TestingLog::Add(1133);
		break;

	case Type::MoveConstructor_Base:
		Trace::out("\t1155 Base(move constructor)%p <- %p \n",p,s);
		TestingLog::Add(1155);
		break;

	case Type::MoveAssignment_Base:
		Trace::out("\t1166 Base(move assignment)%p <- %p \n", p, s);
		TestingLog::Add(1166);
		break;

	case Type::Destructor_Base:
		Trace::out("\t1144 Base(destructor)%p \n",p);
		TestingLog::Add(1144);
		break;

	case Type::SpecializedConstructor_Base:
		Trace::out("\t1177 Base(specialized constructor)%p \n", p);
		TestingLog::Add(1177);
		break;

	case Type::DefaultConstructor_Derived:
		Trace::out("\t2211 Derived(default constructor)%p \n", p);
		TestingLog::Add(2211);
		break;

	case Type::CopyConstructor_Derived:
		Trace::out("\t2222 Derived(copy constructor)%p <- %p \n", p, s);
		TestingLog::Add(2222);
		break;

	case Type::AssignmentOperator_Derived:
		Trace::out("\t2233 tDerived(assignment operator)%p <- %p \n", p, s);
		TestingLog::Add(2233);
		break;

	case Type::MoveConstructor_Derived:
		Trace::out("\t2255 Derived(move constructor)%p <- %p \n", p, s);
		TestingLog::Add(2255);
		break;

	case Type::MoveAssignment_Derived:;
		Trace::out("\t2266 Derived(move assignment)%p <- %p \n", p, s);
		TestingLog::Add(2266);
		break;

	case Type::Destructor_Derived:
		Trace::out("\t2244 Derived(destructor)%p \n", p);
		TestingLog::Add(2244);
		break;

	case Type::SpecializedConstructor_Derived:
		Trace::out("\t2277 Derived(specialized constructor)%p \n", p);
		TestingLog::Add(2277);
		break;

	case Type::DefaultConstructor_Node:
		Trace::out("\t3311 Node(default constructor)%p \n", p);
		TestingLog::Add(3311);
		break;

	case Type::CopyConstructor_Node:
		Trace::out("\t3322 Node(copy constructor)%p <- %p \n", p, s);
		TestingLog::Add(3322);
		break;

	case Type::AssignmentOperator_Node:
		Trace::out("\t3333 Node(assignment operator)%p <- %p \n", p, s);
		TestingLog::Add(3333);
		break;

	case Type::MoveConstructor_Node:
		Trace::out("\t3355 Node(move constructor)%p <- %p \n", p, s);
		TestingLog::Add(3355);
		break;

	case Type::MoveAssignment_Node:;
		Trace::out("\t3366 Node(move assignment)%p <- %p \n", p, s);
		TestingLog::Add(3366);
		break;

	case Type::Destructor_Node:
		Trace::out("\t3344 Node(destructor)%p \n", p);
		TestingLog::Add(3344);
		break;

	case Type::SpecializedConstructor_Node:
		Trace::out("\t3377 Node(specialized constructor)%p \n", p);
		TestingLog::Add(3377);
		break;
	}
}

void TestingLog::Add(int x)
{
	TestingLog* pUTL = TestingLog::privGetInstance();

	pUTL->v.push_back(x);
}

void TestingLog::Reset()
{
	TestingLog* pUTL = TestingLog::privGetInstance();

	pUTL->v.clear();
}

std::vector<int>& TestingLog::GetVector()
{
	TestingLog* pUTL = TestingLog::privGetInstance();

	return pUTL->v;
}

// ---  End of File ---------------
