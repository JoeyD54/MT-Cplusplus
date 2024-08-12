#include "KillThread.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

KillThread::KillThread(const char* const pName, std::promise<void>& _tPromise)
	: BannerBase(pName), mThread(), threadPromise(_tPromise)
{

}

KillThread::~KillThread()
{
	if (this->mThread.joinable())
	{
		this->mThread.join();
		Debug::out("~KillThread() join\n");
	}
}

void KillThread::getKeyPress()
{
	_getch();
	keyPress.cv_key.notify_one();
}

void KillThread::operator()()
{
	START_BANNER

	std::unique_lock<std::mutex> lock_key(keyPress.mtx_key);
	keyPress.cv_key.wait(lock_key);

	Debug::out("Key pressed <----- \n");

	threadPromise.set_value();

	ThreadCountProxy::waitUntilThreadsDone();

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
