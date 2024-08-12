//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Node.h"

// -----------------------------------------------------
//  Do not modify below this line
//  used in tests
// -----------------------------------------------------

Node::Node(const int x)
	: pNext(nullptr),
	n0(x)
{
	Log(TestingLog::SpecializedConstructor_Node);
}

void Node::Log(TestingLog::Type _methodName)
{
	TestingLog::Register(_methodName, this, nullptr);
}

void Node::Log(TestingLog::Type _methodName, const Node &Copy_OR_Move_Argument)
{
	TestingLog::Register(_methodName, this, &Copy_OR_Move_Argument);
}

// --- End of File ---

