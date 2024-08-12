#pragma once

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

class SharedData
{
public:
	SharedData()
		:done(false), endPos(0,0)
	{
	}

	SharedData(const SharedData&) = default;
	SharedData& operator =(const SharedData&) = default;
	~SharedData() = default;

	// -- Data -- //
	std::atomic_bool done = false;
	//std::atomic_bool topFoundColl = false;

	Position endPos;
};

#endif