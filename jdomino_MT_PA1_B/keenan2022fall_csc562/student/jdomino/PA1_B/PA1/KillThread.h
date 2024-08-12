//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ThreadBase.h"

#ifndef KILL_THREAD_H
#define KILL_THREAD_H

struct KillShare;


#define KillEventSetup ThreadCounter TC;

class KillThread : public BannerBase
{
private:
	struct  KeyPress
	{
		std::mutex				 mtx;
		std::condition_variable  cv;
	};

public:

	KillThread(const char* const pName, KillShare& kill_var);

	KillThread() = delete;
	KillThread(const KillThread&) = delete;
	KillThread& operator = (const KillThread&) = delete;
	~KillThread();

	void KeyPressEvent();
	void WaitForKeyPress();
	void SignalThreadsToDie();
	void Launch();
	void operator()();
	
	//------
	// data
	//------

	std::thread mThread;
	KeyPress    keyPress;
	KillShare& kill_var;
};

#endif

// --- End of File ---
