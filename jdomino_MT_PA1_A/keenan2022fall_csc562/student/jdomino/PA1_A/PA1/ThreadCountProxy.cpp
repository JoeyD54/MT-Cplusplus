#include "ThreadCountProxy.h"

void ThreadCountProxy::Increment()
{
	ThreadCountProxy& r = ThreadCountProxy::privGetInstance();

	std::lock_guard<std::mutex> lock(r.mtx);
	r.count++;
	Debug::out("TC:%d \n", r.count);
}

void ThreadCountProxy::Decrement()
{
	ThreadCountProxy& r = ThreadCountProxy::privGetInstance();

	std::lock_guard<std::mutex> lock(r.mtx);
	r.count--;
	Debug::out("TC:%d \n", r.count);

	if (r.count == 0)
	{
		r.cv_thread_count.notify_one();
	}
}

void ThreadCountProxy::waitUntilThreadsDone()
{
	ThreadCountProxy& r = ThreadCountProxy::privGetInstance();

	std::unique_lock<std::mutex> lock_ct(r.mtx_thread_count);
	r.cv_thread_count.wait(lock_ct);
}

//private:

ThreadCountProxy::ThreadCountProxy()
	: count(0), mtx(), mtx_thread_count(), cv_thread_count()
{
}

//Meyers singleton
ThreadCountProxy & ThreadCountProxy::privGetInstance()
{
	static ThreadCountProxy tcp;
	return tcp;
}
