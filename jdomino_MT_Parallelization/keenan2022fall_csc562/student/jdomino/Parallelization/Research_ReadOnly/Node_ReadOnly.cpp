//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Node_ReadOnly.h"

// -----------------------------------------
//     DO NOT MODIFY THIS FILE
// -----------------------------------------

Node::Node()
	: element(),
	pNext(nullptr),
	pRand(nullptr)
{

}

void Node::Print() const
{
	std::string RandElement;
	if (this->pRand == nullptr)
	{
		RandElement = "------";
	}
	else
	{
		RandElement = this->pRand->element;
	}

	Trace::out("%s Addr(%p) pNext(%p) pRand(%p) %s\n",
		this->element.c_str(),
		this,
		this->pNext,
		this->pRand,
		RandElement.c_str());
}

// --- End of File ---
