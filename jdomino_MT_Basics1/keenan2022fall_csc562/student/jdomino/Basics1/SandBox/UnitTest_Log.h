//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef UNIT_TEST_LOG_H
#define UNIT_TEST_LOG_H

#include <vector>

class TestingLog
{
public:
	enum Type
	{
		DefaultConstructor_Base,
		CopyConstructor_Base,
		AssignmentOperator_Base,
		MoveConstructor_Base,
		MoveAssignment_Base,
		Destructor_Base,
		SpecializedConstructor_Base,
		DefaultConstructor_Derived,
		CopyConstructor_Derived,
		AssignmentOperator_Derived,
		MoveConstructor_Derived,
		MoveAssignment_Derived,
		Destructor_Derived,
		SpecializedConstructor_Derived,
		DefaultConstructor_Node,
		CopyConstructor_Node,
		AssignmentOperator_Node,
		MoveConstructor_Node,
		MoveAssignment_Node,
		Destructor_Node,
		SpecializedConstructor_Node
	};

public:
	static void Register(TestingLog::Type, const void*, const void*);
	static void Add(int x);
	static void Reset();
	static std::vector<int>& GetVector();
	static void Create();
	static void Destroy();

private:
	TestingLog() = default;

	static TestingLog* privGetInstance() noexcept
	{
		if(poInstance == nullptr)
		{
			poInstance = new TestingLog();
			assert(poInstance);
		}
		else
		{
			// do nothing
		}

		assert(poInstance);
		return poInstance;
	}

	static TestingLog *poInstance;
	std::vector<int> v;
};

#endif

// ---  End of File ---------------
