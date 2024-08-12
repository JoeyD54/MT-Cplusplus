//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "A.h"
#include "ThreadCount.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

A::A(const char *const pName, std::future<void>& _threadFuture)
	: BannerBase(pName), threadFuture(_threadFuture)
{
}

void A::operator()()
{
	START_BANNER

	ThreadCount tc;

	// Buy time to get all the thread to spin up (only for Basics)
	std::this_thread::sleep_for(10ms);

	int count = 0;
	while (true)
	{
		Debug::out("%d\n", count);
		count++;		

		std::future_status status = this->threadFuture.wait_for(500ms);
		if (status == std::future_status::ready)
		{
			break;
		}
	}
}


// ---  End of File ---
