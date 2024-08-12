//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "D.h"
#include "ThreadCount.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

D::D(const char *const pName, std::future<void>& _threadFuture)
	: BannerBase(pName), threadFuture(_threadFuture)
{
}

void D::operator()()
{
	START_BANNER
	
	ThreadCount tc;

	// Buy time to get all the thread to spin up (only for Basics)
	std::this_thread::sleep_for(10ms);

	const char *pStoryOriginal = "<0><1><2><3><4><5><6><7><8>";
	size_t  len = strlen(pStoryOriginal);
	char *pString = new char[len + 1];
	strcpy_s(pString, len + 1, pStoryOriginal);

	int tmpLen = (int)(len - 1);

	while (true)
	{
		if (tmpLen <= 0)
		{
			tmpLen = (int)(len - 1);
			strcpy_s(pString, len + 1, pStoryOriginal);
		}

		Debug::out("%s\n", pString);
		pString[tmpLen--] = 0;
		pString[tmpLen--] = 0;
		pString[tmpLen--] = 0;

		std::future_status status = this->threadFuture.wait_for(500ms);
		if (status == std::future_status::ready)
		{
			break;
		}
	}

	delete pString;
}

// ---  End of File ---
