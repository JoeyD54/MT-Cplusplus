//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef FILE_COORD_SHARE_H
#define FILE_COORD_SHARE_H

struct FileCoordShare
{
	enum class Status
	{
		FileThreadBufferEmpty,
		FileThreadBufferReady,
		FileThreadBufferTransfering,
		Uninitialized,
		DONE
	};

	std::mutex				 mtx;
	std::condition_variable  cv;
	Status status;
};

#endif

// --- End of File ---
