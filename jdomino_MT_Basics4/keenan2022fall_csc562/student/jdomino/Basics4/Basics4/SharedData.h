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
public:
	SharedData();
	SharedData(const SharedData &) = default;
	SharedData &operator =(const SharedData &) = default;
	~SharedData() = default;

	// ---------------------------------------------------------------
	// Add methods (optional)
	// ---------------------------------------------------------------



	// ---------------------------------------------------------------
	// Data 
	//      DO NOT add or modify any data
	// ---------------------------------------------------------------
	unsigned short value;
	unsigned short complement;
	unsigned short count;
	std::mutex mtx;
	std::condition_variable cv;
};

#endif

// --- End of File ---

