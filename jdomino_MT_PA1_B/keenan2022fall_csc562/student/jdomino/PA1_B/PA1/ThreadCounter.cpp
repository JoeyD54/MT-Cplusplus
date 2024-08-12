#include "ThreadCounter.h"
#include "ThreadCountManager.h"

ThreadCounter::ThreadCounter()
{
	ThreadCountManager::Increment();
}

ThreadCounter::~ThreadCounter()
{
	ThreadCountManager::Decrement();
}