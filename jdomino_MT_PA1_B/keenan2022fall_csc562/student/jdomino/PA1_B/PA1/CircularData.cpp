#include "CircularData.h"

bool CircularData::IsEmpty()
{
	return this->empty;
}

CircularData::CircularData()
	: front(CIRCULAR_DATA_SIZE),
	back(CIRCULAR_DATA_SIZE),
	empty(true),
	full(false)
{
	// initialized data
	for (int i = 0; i < CIRCULAR_DATA_SIZE; i++)
	{
		this->data[i] = 0;
	}
}

CircularData::~CircularData()
{
	// free any commands in queue
	Command* pCmd;
	while (this->PopFront(pCmd))
	{
		delete pCmd;
	}
}

bool CircularData::PushBack(Command* pCmd)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	assert(pCmd);
	bool status = true;

	// If there's room
	if (this->front != this->back || this->empty)
	{
		// add data
		this->data[this->back.Index()] = pCmd;
		this->back++;
		this->empty = false;

		//We full?
		if (this->front == this->back)
		{
			this->full = true;
			assert(false);
		}
	}
	else
	{
		status = false;
	}

	return status;
}

bool CircularData::PopFront(Command*& pCmd)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	bool status = true;

	// Is there data to process?
	if (this->front != this->back || this->full)
	{
		// Grab one
		pCmd = this->data[this->front.Index()];
		this->front++;

		this->full = false;

		// Empty?
		if (this->front == this->back)
		{
			this->empty = true;
		}
	}
	else
	{
		status = false;
	}
	return status;
}

//---  End of File ---
