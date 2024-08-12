
#include "CircularIndex.h"

CircularIndex::CircularIndex(unsigned int buffSize)
{
	this->size = buffSize;
	this->mask = (unsigned int)(buffSize - 1);

	// buffsize must be power of 2
	assert((size & (size - 1)) == 0);
	this->index = 0;
}

// postfix
unsigned int CircularIndex::operator++(int)
{
	this->index++;

	// Get last 2 bits
	this->index = this->index & this->mask;
	return this->index;
}

bool CircularIndex::operator==(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return (this->index == tmp.index);
}

bool CircularIndex::operator!=(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return (this->index != tmp.index);
}

unsigned int CircularIndex::Index() const
{
	return this->index;
}

//---  End of File ---
