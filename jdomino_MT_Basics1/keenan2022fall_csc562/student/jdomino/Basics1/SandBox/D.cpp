//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "D.h"

	//Dig 6
	//1 Default constructor
D::D()
	:C(), d0(0)
{
	this->poHead = nullptr;

	Log(TestingLog::DefaultConstructor_Derived);
}

//2 Copy constructor
D::D(const D& in)
	:C(in), d0(in.d0)
{
	Node * pTemp = in.poHead;
	while (pTemp != nullptr)
	{
		if (this->poHead == nullptr)
		{
			this->poHead = new Node(*pTemp);
		}
		else
		{
			
			Node * newNode = new Node(*pTemp);
			newNode->pNext = this->poHead;
			this->poHead = newNode;
		}

		pTemp = pTemp->pNext;
	}




	Log(TestingLog::CopyConstructor_Derived, in);
}

//3 Assignment Operator
D& D:: operator = (const D& in)
{
	if (this->poHead != nullptr)
	{
		Node* pWalk = this->poHead;
		Node* pDelNode = pWalk;
		while (pWalk != nullptr)
		{
			
			pWalk = pWalk->pNext;
			delete pDelNode;
			pDelNode = pWalk;
		}

		this->poHead = nullptr;
	}

	C::operator=(in);

	this->d0 = in.d0;

	Node* pTemp = in.poHead;
	while (pTemp != nullptr)
	{
		if (this->poHead == nullptr)
		{
			this->poHead = new Node(*pTemp);
		}
		else
		{

			Node* newNode = new Node(*pTemp);
			newNode->pNext = this->poHead;
			this->poHead = newNode;
		}

		pTemp = pTemp->pNext;
	}

	Log(TestingLog::AssignmentOperator_Derived, in);

	return *this;
}

//4 Destructor
D::~D()
{
	Node * pTemp = this->poHead;
	while (pTemp != nullptr)
	{
		this->poHead = this->poHead->pNext;
		delete pTemp;
		pTemp = this->poHead;
	}

	Log(TestingLog::Destructor_Derived);
}

//5 Move Constructor
D::D(D&& in) noexcept
	:C(std::move(in)), d0{ in.d0 }, poHead{ in.poHead }
{
	// clear
	in.d0 = 0;
	in.poHead = nullptr;

	Log(TestingLog::MoveConstructor_Derived, in);
}

//6 Assignment Move
D& D::operator = (D&& in) noexcept
{
	if (this != &in)
	{
		//Release
		if (this->poHead != nullptr)
		{
			Node* pWalk = this->poHead;
			Node* pDelNode = pWalk;
			while (pWalk != nullptr)
			{
				pWalk = pWalk->pNext;
				delete pDelNode;
				pDelNode = pWalk;
			}
			this->poHead = nullptr;
		}

		this->d0 = 0;

		// move
		C::operator=(std::move(in));
		this->d0 = std::move(in.d0);
		this->poHead = std::move(in.poHead);			

		// clear
		in.d0 = 0;
		in.poHead = nullptr;
	}
	Log(TestingLog::MoveAssignment_Derived, in);
	return *this;
}

// ---- End of File ----
