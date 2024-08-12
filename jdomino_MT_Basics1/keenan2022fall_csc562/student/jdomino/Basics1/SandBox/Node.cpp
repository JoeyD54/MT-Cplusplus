//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Node.h"

Node::Node()
	: pNext(nullptr), n0(0x99)
{
	Log(TestingLog::DefaultConstructor_Node);
}

Node::Node(const Node &tmp)
	: pNext(nullptr),
	n0(tmp.n0)
{
	Log(TestingLog::CopyConstructor_Node, tmp);
}

Node &Node::operator = (const Node &tmp)
{
	if (this != &tmp)
	{
		this->pNext = nullptr;
		this->n0 = tmp.n0;
	}
	Log(TestingLog::AssignmentOperator_Node, tmp);
	return *this;
}

Node::~Node()
{
	Log(TestingLog::Destructor_Node);
}


Node::Node(Node &&tmp) noexcept
	// move
	:pNext(std::move(tmp.pNext)),
	n0(std::move(tmp.n0))
{
	// clear
	tmp.pNext = nullptr;
	tmp.n0 = 0;
	Log(TestingLog::MoveConstructor_Node, tmp);
}

Node &Node::operator = (Node &&tmp) noexcept
{
	if (this != &tmp)
	{
		// release
		this->pNext = nullptr;
		this->n0 = 0;

		// move
		this->pNext = std::move(tmp.pNext);
		this->n0 = std::move(tmp.n0);

		// clear
		tmp.pNext = nullptr;
		tmp.n0 = 0;
	}
	Log(TestingLog::MoveAssignment_Node, tmp);
	return *this;
}



// ---- End of File ----
