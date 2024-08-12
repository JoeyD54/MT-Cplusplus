//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Consumer_X.h"

// -------------------------------------
//  MODIFY - make changes to this file
// -------------------------------------

void Consumer_X::operator() (SharedData &r, std::chrono::system_clock::time_point tToc)
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
		// --> Update the complement using condition variable using wait_until
		// ------------------------------------------------------------------------

		
		if (r.cv.wait_until(locker, tToc, [&]() { return r.complement == 0 && r.value != 0 ;}))
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
