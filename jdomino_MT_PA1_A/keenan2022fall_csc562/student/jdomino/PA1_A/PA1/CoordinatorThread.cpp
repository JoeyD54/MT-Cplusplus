#include "CoordinatorThread.h"

CoordinatorThread::CoordinatorThread(const char* const pName, std::future<void>& _tFuture, FileCoorShare& _inFCS, CircularData& _inCircleBuffer)
	:BannerBase(pName),
	mThread(),
	pBuff_A(new Buffer(CoordinatorThread::BUFFER_SIZE)),
	pBuff_B(new Buffer(CoordinatorThread::BUFFER_SIZE)),
	share_fc(_inFCS),
	tFuture(_tFuture),	
	inCircleData(_inCircleBuffer)
{
}

CoordinatorThread::~CoordinatorThread()
{
	if (this->mThread.joinable())
	{
		this->mThread.join();
		Debug::out("~CoordinatorThread() join\n");
	}
}

void CoordinatorThread::operator()()
{
	START_BANNER

	ThreadCount TC;

	int count = 0;
	while (true)
	{
		std::this_thread::sleep_for(1s);

		std::unique_lock<std::mutex> lock(share_fc.mtx);
		if (share_fc.cv.wait_for(lock, 0ms, [&]() { return (share_fc.status == FileCoorShare::Status::Ready); }))
		{
			share_fc.status = FileCoorShare::Status::Transfer;
		}

		lock.unlock();

		if (share_fc.status == FileCoorShare::Status::Transfer)
		{
			Debug::out("     File: Coordinator transfer start\n");
			
			FileThread::CopyBuffer(this->pBuff_A);
			
			share_fc.status = FileCoorShare::Status::Empty;

			Debug::out("     File: Coordinator transfer end\n");
		}

		//std::future_status killStatus = this->tFuture.wait_for(0ms);
		//if (killStatus == std::future_status::ready)
		//{
		//	break;
		//}
	}
}

void CoordinatorThread::Launch()
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