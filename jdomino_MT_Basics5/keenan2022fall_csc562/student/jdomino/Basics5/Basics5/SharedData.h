//------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//------------------------------------------------------------

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

// -----------------------
//  DO NOT MODIFY
// -----------------------

class SharedData
{

	// ---------------------------------------------------------------
	// Add methods (optional)
	// ---------------------------------------------------------------
	SharedData();
	SharedData(const SharedData&) = default;
	SharedData& operator=(const SharedData&) = default;
	~SharedData() = default;

	// ---------------------------------------------------------------
	// Data 
	// ---------------------------------------------------------------
	
	std::mutex mtx;
	std::condition_variable cv;
	bool flag;
};

#endif

// --- End of File ---

