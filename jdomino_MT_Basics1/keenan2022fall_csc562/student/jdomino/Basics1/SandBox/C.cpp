//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "C.h"


//Big 6

//1 Default constructor
C::C()
	: c0(0), poString(nullptr)
{
	Log(TestingLog::DefaultConstructor_Base);

}

//2 Copy Constructor
C::C(const C& in)
	:c0(in.c0)
{
	delete this->poString;

	size_t size = strlen(in.poString) + 1;
	this->poString = new char[size]();
	memcpy_s(this->poString, size, in.poString, size);

	//this->poString = in.poString;

	Log(TestingLog::CopyConstructor_Base, in);
}

//3 Assignment Operator
C& C::operator = (const C& in)
{
	this->c0 = in.c0;
	delete this->poString;
	
	size_t size = strlen(in.poString) + 1;
	this->poString = new char[size]();
	memcpy_s(this->poString, size, in.poString, size);

	Log(TestingLog::AssignmentOperator_Base, in);

	return *this;
}

//4 Destructor
C::~C()
{
	this->c0 = 0;
	delete this->poString;
	this->poString = nullptr;

	Log(TestingLog::Destructor_Base);
}

//5 Move Constructor
C::C(C&& in) noexcept
	:c0(std::move(in.c0)), poString(std::move(in.poString))
{

	// clear
	in.c0 = 0;
	in.poString = nullptr;

	Log(TestingLog::MoveConstructor_Base, in);
}

//6 Assignment Move
C& C::operator = (C&& in) noexcept
{
	if (this != &in)
	{
		// release
		this->c0 = 0;
		delete this->poString;

		// move
		this->c0 = std::move(in.c0);
		this->poString = std::move(in.poString);
		
		// clear
		in.c0 = 0;
		in.poString = nullptr;
	}
	Log(TestingLog::MoveAssignment_Base, in);
	return *this;
}

// ---- End of File ----
