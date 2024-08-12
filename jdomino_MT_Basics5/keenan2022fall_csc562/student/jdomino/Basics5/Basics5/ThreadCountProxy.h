#ifndef THREAD_COUNT_PROXY_H
#define THREAD_COUNT_PROXY_H

using namespace ThreadFramework;

struct ThreadCountProxy
{
public:
	static void Increment()
	{
		ThreadCountProxy& r = ThreadCountProxy::privGetInstance();

		std::lock_guard<std::mutex> lock(r.mtx);
		r.count++;
		Debug::out("TC:%d \n", r.count);
	}

	static void Decrement()
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

	static void waitUntilThreadsDone()
	{
		ThreadCountProxy& r = ThreadCountProxy::privGetInstance();

		std::unique_lock<std::mutex> lock_ct(r.mtx_thread_count);
		r.cv_thread_count.wait(lock_ct);
	}

private:

	ThreadCountProxy()
		: count(0), mtx(), mtx_thread_count(), cv_thread_count()
	{

	}

	//Myers singleton
	static ThreadCountProxy& privGetInstance()
	{
		static ThreadCountProxy tcp;
		return tcp;
	}

	int count;
	std::mutex mtx;

	std::mutex				mtx_thread_count;
	std::condition_variable cv_thread_count;
};

#endif