//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Consumer_Y.h"

// -------------------------------------
//  MODIFY - make changes to this file
// -------------------------------------

void Consumer_Y::operator() (SharedData &r, std::chrono::system_clock::time_point tToc)
{
	START_BANNER

	//---------------------------
	// DO WORK HERE (optional)
	//---------------------------

	std::unique_lock<std::mutex> locker(r.mtx);

	// Safety to end thread... do not change.
	while (std::chrono::system_clock::now() < tToc)   // <---- A
	{
		// ------------------------------------------------------------------------
		// --> Update the complement using condition variable using wait_for
		// ------------------------------------------------------------------------
		
		if (r.cv.wait_for(locker, tToc - std::chrono::system_clock::now(), [&]() { return r.complement == 0 && r.value != 0; }))
		{
			r.complement = ~(r.value);
		}
		else
		{
			break;
		}

		//---------------------------
		// DO WORK HERE (optional)
		//---------------------------

		// Required for tests - make sure you call this one
		Display(r);
	}
}

// --- End of File ---
