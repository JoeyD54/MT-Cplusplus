#include "ThreadCount.h"

ThreadCount::ThreadCount()
{
    ThreadCountProxy::Increment();
}


ThreadCount::~ThreadCount()
{
    ThreadCountProxy::Decrement();
}