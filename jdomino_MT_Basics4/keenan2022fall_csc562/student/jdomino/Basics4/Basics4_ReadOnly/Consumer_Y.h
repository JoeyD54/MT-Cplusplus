//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef CONSUMER_Y_H
#define CONSUMER_Y_H

#include "SharedData.h"

using namespace ThreadFramework;

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Consumer_Y : public BannerBase
{
public:
	Consumer_Y() = delete;
	Consumer_Y(const Consumer_Y &) = default;
	Consumer_Y &operator =(const Consumer_Y &) = default;
	~Consumer_Y() = default;

	Consumer_Y(const char *const name);

	// function call operator
	void operator() (SharedData &d, std::chrono::system_clock::time_point tToc);

	// Display and Recording for unit test
	void Display(const SharedData &r);
};

#endif

// --- End of File ---
