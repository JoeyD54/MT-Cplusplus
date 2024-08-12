#pragma once
#include "KillShare.h"

class ThreadBase : public BannerBase
{
public:
	ThreadBase() = delete;
	//default
	ThreadBase(const ThreadBase&) = delete;
	ThreadBase& operator = (const ThreadBase&) = delete;
	~ThreadBase();

	ThreadBase(const char* const pName, KillShare& _kill_var);
	
	void virtual operator()();
	void virtual Launch();
	bool virtual KillEvent();

	KillShare& getKill();

private:
	//data
	std::thread mThread;
	KillShare& kill_var;
};

