//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Controller.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

Controller::Controller(const char *const pName)
	: BannerBase(pName)
{
}

void Controller::getKeyPress()
{
	_getch();
	keyPress.cv_key.notify_one();
}

void Controller::operator()(std::promise<void>& threadPromise)
{
	START_BANNER

	std::unique_lock<std::mutex> lock_key(keyPress.mtx_key);
	keyPress.cv_key.wait(lock_key);

	threadPromise.set_value();

	ThreadCountProxy::waitUntilThreadsDone();
	
 }

// ---  End of File ---
