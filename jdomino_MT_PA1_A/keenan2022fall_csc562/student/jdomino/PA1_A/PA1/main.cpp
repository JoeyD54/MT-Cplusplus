//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <conio.h>
#include "KillThread.h"
#include "FileThread.h"
#include "CoordinatorThread.h"
#include "FileCoorShare.h"

int main()
{
	START_BANNER_MAIN("-Main-");

	// ----------------------------------------------------------------
	// setup objects
	//-----------------------------------------------------------------

	std::promise<void> tKillPromise;
	std::future<void> tKillFuture = tKillPromise.get_future();

	FileCoorShare fileCoorShare;
	CircularData circularData;

	KillThread tKill("--KILL--", tKillPromise);
	FileThread tFile("--FILE--", tKillFuture, fileCoorShare);
	CoordinatorThread tCoor("--COOR--", tKillFuture, fileCoorShare, circularData);

	tFile.Launch();
	tCoor.Launch();
	tKill.Launch();



	tKill.getKeyPress();



}

// --- End of File ---
