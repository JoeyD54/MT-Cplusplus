//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef CONSUMER_Z_H
#define CONSUMER_Z_H

#include "SharedData.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Consumer_Z : public BannerBase
{
public:
	Consumer_Z() = delete;
	Consumer_Z(const Consumer_Z &) = default;
	Consumer_Z &operator =(const Consumer_Z &) = default;
	~Consumer_Z() = default;

	Consumer_Z(const char *const name);

	// function call operator
	void operator() (SharedData &d, std::chrono::system_clock::time_point tToc);

	// Display and Recording for unit test
	void Display(const SharedData &r);
};

#endif

// --- End of File ---
