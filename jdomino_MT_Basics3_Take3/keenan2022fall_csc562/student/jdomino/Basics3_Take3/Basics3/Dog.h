//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef DOG_H
#define DOG_H

#include "AlphaDog.h"

class Dog
{
public:
	enum class Name
	{
		Fido,
		Snoopy,
		Rex,
		Killer,
		Fluffy,
		None
	};

public:
	Dog();
	Dog(const Dog &) = default;
	Dog &operator = (const Dog &) = default;
	~Dog() = default;

	Dog(Name _name);

	const char *GetName() const;

	// function call operator
	void operator()(Dog &in, AlphaDog &alpha);

// -------------------------
//  Data:
// -------------------------
	Name name;
};

#endif