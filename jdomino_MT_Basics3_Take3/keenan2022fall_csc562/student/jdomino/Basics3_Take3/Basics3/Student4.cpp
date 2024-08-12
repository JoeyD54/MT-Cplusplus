//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Student4.h"

using namespace ThreadFramework;

// -----------------------
//  DO NOT MODIFY
// -----------------------

static const char *StringName[4]
{
	"Lisa",
	"Jim ",
	"Mike",
	"Jay "
};

Student4::Student4(Name _name, int StartValue)
	: mtx(), score(StartValue), name(_name)
{

}

const char *Student4::GetName() const
{
	return StringName[(int)this->name];
}

// --- End of File ---
