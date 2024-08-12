

#ifndef CIRCULAR_INDEX_H
#define CIRCULAR_INDEX_H
class CircularIndex
{
public:
	CircularIndex(unsigned int buffSize);

	CircularIndex() = delete;
	CircularIndex(const CircularIndex&) = delete;
	const CircularIndex& operator = (const CircularIndex&) = delete;
	~CircularIndex() = default;

	unsigned int operator++(int);
	bool operator==(const CircularIndex & tmp);
	bool operator!=(const CircularIndex & tmp);

	unsigned int Index() const;

private:
	unsigned int index;
	unsigned int size;
	unsigned int mask;
};


#endif
