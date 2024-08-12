//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "B.h"
#include "ThreadCount.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

B::B(const char* const pName, std::future<void>& _threadFuture)
	: BannerBase(pName), threadFuture(_threadFuture)
{
}

void B::operator()()
{
	START_BANNER

	ThreadCount tc;

	// Buy time to get all the thread to spin up (only for Basics)
	std::this_thread::sleep_for(10ms);

	int count = 0x10000;
	while (true)
	{
		Debug::out("0x%x\n", count);
		count--;

		std::this_thread::sleep_for(2s);

		std::future_status status = this->threadFuture.wait_for(1s);
		if (status == std::future_status::ready)
		{
			break;
		}
	}
};


// ---  End of File ---
