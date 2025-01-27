//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <conio.h>
#include "KillEventWrapper.h"
#include "FileThread.h"
#include "CoordinatorThread.h"
#include "FileCoordShare.h"
#include "PlaybackThread.h"
#include "WaveBuffthread.h"

//coordinator share
struct FileCoorShare
{
	std::mutex file_mtx;
	std::condition_variable file_cv;
};


int main()
{
	START_BANNER_MAIN("-Main-");

	KillShare killShare;
	FileCoordShare fileCoordShare;
	CircularData circleData;

	FileThread tFile("--FILE--", killShare, fileCoordShare);
	CoordinatorThread tCoord("--COORD--", killShare, fileCoordShare, circleData);
	PlaybackThread tPlayback("--PLAY--", killShare, circleData);

	tFile.Launch();
	tCoord.Launch();
	tPlayback.Launch();
}

// --- End of File ---
