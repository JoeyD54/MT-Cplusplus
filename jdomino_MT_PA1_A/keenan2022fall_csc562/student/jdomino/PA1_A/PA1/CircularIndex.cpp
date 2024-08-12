#include "CircularIndex.h"

CircularIndex::CircularIndex(unsigned int buffSize)
{

    this->size = buffSize;
    this->mask = (unsigned int)(buffSize - 1);

    // verify that buffSize is a power of 2
    assert((size & (size - 1)) == 0);

    this->index = 0;
}

// postfix
unsigned int CircularIndex::operator++(int)
{
    this->index++;

    // Circular - use this to take the last 2 bits, and auto wrap
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