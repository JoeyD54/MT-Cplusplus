
#ifndef KILL_SHARE_H
#define KILL_SHARE_H

struct KillShare
{
	std::promise<void> prom;
	std::future<void>  fu = prom.get_future();
};

#endif
