#ifndef FILE_COOR_SHARE_H
#define FILE_COOR_SHARE_H

struct FileCoorShare
{
	enum class Status
	{
		Empty,
		Ready,
		Transfer,
		Uninitialize
	};

	std::mutex				mtx;
	std::condition_variable cv;

	Status status;
};

#endif
