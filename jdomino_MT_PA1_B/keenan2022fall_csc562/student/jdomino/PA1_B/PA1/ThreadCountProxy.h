#ifndef THREAD_COUNT_PROXY_H
#define THREAD_COUNT_PROXY_H

struct ThreadCountProxy
{
public:
	static void Increment();
	static void Decrement();
	static void waitUntilThreadsDone();

private:

	ThreadCountProxy();
	//Myers singleton
	static ThreadCountProxy& privGetInstance();

	int count;
	std::mutex mtx;

	std::mutex				mtx_thread_count;
	std::condition_variable cv_thread_count;
};

#endif

