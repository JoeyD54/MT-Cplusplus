//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef CONSUMER_X_H
#define CONSUMER_X_H

#include "SharedData.h"

using namespace ThreadFramework;

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Consumer_X : public BannerBase
{
public:
	Consumer_X() = delete;
	Consumer_X(const Consumer_X &) = default;
	Consumer_X &operator =(const Consumer_X &) = default;
	~Consumer_X() = default;

	Consumer_X(const char *const name);

	// function call operator
	void operator() (SharedData &d, std::chrono::system_clock::time_point tToc);

	// Display and Recording for unit test
	void Display(const SharedData &r);
};

#endif

// --- End of File ---
