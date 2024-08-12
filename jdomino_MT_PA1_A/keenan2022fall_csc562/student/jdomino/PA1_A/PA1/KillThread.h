#ifndef KILL_THREAD_H
#define KILL_THREAD_H


#include <conio.h>
#include "ThreadCount.h"

using namespace ThreadFramework;

class KillThread : public BannerBase
{
private:
	struct KeyPress
	{
		std::mutex mtx_key;
		std::condition_variable cv_key;
	};

public:
	KillThread() = delete;
	KillThread(const char* const pName, std::promise<void>& _tPromise);
	~KillThread();

	void getKeyPress();
	void operator()();
	void Launch();

	// Data
	KeyPress keyPress;
	std::thread mThread;
	std::promise<void>& threadPromise;

};

#endif
