//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Producer.h"

// -----------------------
//  DO NOT MODIFY
// -----------------------

void Producer::operator() (SharedData &r, std::chrono::system_clock::time_point tToc, bool NotifyAll_flag)
{
	START_BANNER

	// Seed
	srand(0x2020);
	int i = 0;

	// Time out... abort if time is greater than tToc
	while (std::chrono::system_clock::now() < tToc)
	{
		// Mutex protect the shared data
		std::unique_lock<std::mutex> lock(r.mtx);

			r.value = Prod_data[i];
			r.complement = 0;
			r.count = static_cast<unsigned short> (rand() % 0xFFFF);
			
			Debug::out("--> %x\n", r.value);
		
		lock.unlock();
		
		// Notify the consumers...
		if (NotifyAll_flag)
		{
			r.cv.notify_all();
		}
		else
		{
			r.cv.notify_one();
		}

		// Do Not sleep more that tToc
		std::chrono::system_clock::duration delta;
		auto tTic = std::chrono::system_clock::now();
		if (tTic < tToc)
		{
			// How much time elapsed?
			delta = tToc - tTic;
			
			// Do we have enough of time to do a scheduled sleep?
			if (delta > sleepTime[i])
			{
				delta = sleepTime[i];
			}
			std::this_thread::sleep_for(delta);
		}

		i++;
	}

}

// --- End of File ---
