//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "A.h"

//Big 6

//1 Default constructor
A::A()
	: a0(0), a1(0)
{
	Log(TestingLog::DefaultConstructor_Base);

}

//2 Copy Constructor
A::A(const A& in)
	:a0(in.a0), a1(in.a1)
{
	Log(TestingLog::CopyConstructor_Base, in);
}

//3 Assignment Operator
A & A::operator = (const A& in) 
{
	this->a0 = in.a0;
	this->a1 = in.a1;

	Log(TestingLog::AssignmentOperator_Base, in);

	return *this;
}

//4 Destructor
A::~A()
{
	Log(TestingLog::Destructor_Base);
}

//5 Move Constructor
A::A(A&& in) noexcept
	:a0(std::move(in.a0)), a1(std::move(in.a1))
{
	// clear
	in.a0 = 0;
	in.a1 = 0;

	Log(TestingLog::MoveConstructor_Base, in);
}

//6 Assignment Move
A& A::operator = (A&& in) noexcept
{
	if (this != &in)
	{
		// release
		this->a0 = 0;
		this->a1 = 0;

		// move
		this->a0 = std::move(in.a0);
		this->a1 = std::move(in.a1);

		// clear
		in.a0 = 0;
		in.a1 = 0;
	}
	Log(TestingLog::MoveAssignment_Base, in);
	return *this;
}


// ---- End of File ----
