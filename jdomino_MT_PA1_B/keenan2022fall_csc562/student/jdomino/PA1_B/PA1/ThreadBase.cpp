#include "ThreadBase.h"
#include "KillEventWrapper.h"


ThreadBase::ThreadBase(const char* const pName, KillShare& _kill_var)
	:BannerBase(pName), mThread(), kill_var(_kill_var)
{
}

void ThreadBase::operator()()
{
	//overridden in new classes
}

void ThreadBase::Launch()
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

bool ThreadBase::KillEvent()
{
	//exit condition - keep at 0s
	return (kill_var.fu.wait_for(0s) == std::future_status::ready);
}

KillShare& ThreadBase::getKill()
{
	return this->kill_var;
}

ThreadBase::~ThreadBase()
{
	if (this->mThread.joinable())
	{
		this->mThread.join();
	}
}