//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef CONSUMER_W_H
#define CONSUMER_W_H

#include "SharedData.h"

using namespace ThreadFramework;

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Consumer_W : public BannerBase
{
public:
	Consumer_W() = delete;
	Consumer_W(const Consumer_W &) = default;
	Consumer_W &operator =(const Consumer_W &) = default;
	~Consumer_W() = default;

	Consumer_W(const char *const name);

	// function call operator
	void operator() (SharedData &d, std::chrono::system_clock::time_point tToc);

	// Display and Recording for unit test
	void Display(const SharedData &r);
};

#endif

// --- End of File ---
