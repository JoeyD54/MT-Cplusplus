//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Controller_H

#include <conio.h>
#include "ThreadCount.h"

using namespace ThreadFramework;

class Controller : public BannerBase
{
private:
	struct KeyPress
	{
		std::mutex mtx_key;
		std::condition_variable cv_key;
	};

public:
	Controller() = delete;
	Controller(const char* const pName);

	void getKeyPress();

	void operator()(std::promise<void>& threadPromise);

	// Data
	KeyPress keyPress;

};
#endif

// ---  End of File ---
