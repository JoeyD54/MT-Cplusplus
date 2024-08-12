//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "B.h"

	//Big 6
	//1 Default constructor
B::B()
	:A(), b0(0), b1(0)
{
	Log(TestingLog::DefaultConstructor_Derived);
}

//2 Copy constructor
B::B(const B& in)
	:A(in), b0(in.b0), b1(in.b1)
{
	Log(TestingLog::CopyConstructor_Derived, in);
}

//3 Assignment Operator
B & B:: operator = (const B& in)
{
	A::operator=(in);

	this->b0 = in.b0;
	this->b1 = in.b1;

	Log(TestingLog::AssignmentOperator_Derived, in);

	return *this;
}

//4 Destructor
B::~B()
{
	Log(TestingLog::Destructor_Derived);
}

//5 Move Constructor
B::B(B&& in) noexcept
	:A(std::move(in)), b0(std::move(in.b0)), b1(std::move(in.b1))
{		
		// clear
		in.b0 = 0;
		in.b1 = 0;

		Log(TestingLog::MoveConstructor_Derived, in);
}

//6 Assignment Move
B& B::operator = (B&& in) noexcept
{
	A::operator=(std::move(in));

	if (this != &in)
	{
		// release
		this->b0 = 0;
		this->b1 = 0;

		// move
		this->b0 = std::move(in.b0);
		this->b1 = std::move(in.b1);

		// clear
		in.b0 = 0;
		in.b1 = 0;
	}
	Log(TestingLog::MoveAssignment_Derived, in);
	return *this;
}

// ---- End of File ----
