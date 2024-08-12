//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <conio.h>

#include "ThreadCountManager.h"
#include "KillEventWrapper.h"

KillThread::KillThread(const char* const pName, KillShare& _kill_var)
	: BannerBase(pName),
	keyPress(),
	kill_var(_kill_var)
{
}

void KillThread::KeyPressEvent()
{
	_getch();
	this->keyPress.cv.notify_one();
}

void KillThread::WaitForKeyPress()
{
	std::unique_lock<std::mutex> lock_key(this->keyPress.mtx);
	this->keyPress.cv.wait(lock_key);

	Debug::out("key pressed <----  \n");
}

void KillThread::Launch()
{
	if (this->mThread.joinable() == false)
	{
		this->mThread = std::thread(std::ref(*this));
	}
	else
	{
		assert(false);
	}
}

void KillThread::SignalThreadsToDie()
{
	// KILL!!! KILL THEM!!!!
	kill_var.prom.set_value();
}

void KillThread::operator()()
{
	START_BANNER

	this->WaitForKeyPress();

	this->SignalThreadsToDie();

	ThreadCountManager::WaitUntilThreadDone();
}

KillThread::~KillThread()
{
	Debug::out("~KillThread()  join \n");
	//calls base destructor -  dont even think I need this
	if (this->mThread.joinable())
	{
		this->mThread.join();
		Debug::out("~CoordThread()  join \n");
	}
}


// --- End of File ---
