//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#include "Consumer_Z.h"

// -------------------------------------
//  MODIFY - make changes to this file
// -------------------------------------

void Consumer_Z::operator() (SharedData &r, std::chrono::system_clock::time_point tToc)
{
	START_BANNER

	//---------------------------
	// DO WORK HERE (optional)
	//---------------------------

	// Safety to end thread... do not change.
	while (std::chrono::system_clock::now() < tToc)   // <---- A
	{
		// ------------------------------------------------------------------------
		// --> Update the complement using condition variable using wait_until
		// ------------------------------------------------------------------------
		
		//---------------------------
		// DO WORK HERE (optional)
		//---------------------------

		// Required for tests - make sure you call this one
		Display(r);
	}
}

// --- End of File ---
