//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "C.h"
#include "ThreadCount.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

C::C(const char *const pName, std::future<void>& _threadFuture)
	: BannerBase(pName), threadFuture(_threadFuture)
{
}

void C::operator()()
{
	START_BANNER

	ThreadCount tc;

	// Buy time to get all the thread to spin up (only for Basics)
	std::this_thread::sleep_for(10ms);

	const char *pFruit[] =
	{
		{"apple"},
		{"orange"},
		{"banana"},
		{"lemon"}
	};

	int count = 0;
	while (true)
	{
		int i = count++ % 4;
		Debug::out("%s\n", pFruit[i]);

		

		std::future_status status = this->threadFuture.wait_for(500ms);
		if (status == std::future_status::ready)
		{
			break;
		}
	}
}

// ---  End of File ---
