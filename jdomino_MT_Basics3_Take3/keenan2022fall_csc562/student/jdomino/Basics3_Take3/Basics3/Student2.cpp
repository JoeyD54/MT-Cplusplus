//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Student2.h"

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

Student2::Student2(Name _name, int StartValue)
	:mtx(), score(StartValue), name(_name)
{

}

const char *Student2::GetName() const
{
	return StringName[(int)this->name];
}

// --- End of File ---
