//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef PRODUCER_H
#define PRODUCER_H

#include "SharedData.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

// -----------------------
//  DO NOT MODIFY
// -----------------------

class Producer : public BannerBase
{
public:
	const unsigned short Prod_data[15]
	{
		0xAAAA,
		0xBBBB,
		0x4444,
		0xCCCC,
		0xEEEE,
		0x1111,
		0x6666,
		0x3333,
		0x2222,
		0x5555,
		0x7777,
		0x8888,
		0x9999,
		0xDDDD,
		0xFFFF
	};

	const std::chrono::system_clock::duration sleepTime[15]
	{
		2000ms,
		4000ms,
		1500ms,
		250ms,
		150ms,
		150ms,
		500ms,
		2200ms,
		2200ms,
		2000ms,
		1000ms,
		5000ms,
		1200ms,
		800ms,
		500ms
	};

public:
	Producer() = delete;
	Producer(const Producer &) = default;
	Producer &operator =(const Producer &) = default;
	~Producer() = default;

	Producer(const char *const name);

	// function call operator
	void operator() (SharedData &data, 
		std::chrono::system_clock::time_point tToc, 
		bool NotifyAll_flag = false);

};

#endif

// --- End of File ---

