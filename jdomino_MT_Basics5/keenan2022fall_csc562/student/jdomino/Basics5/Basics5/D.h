//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef D_H

using namespace ThreadFramework;

class D : public BannerBase
{
public:
	D() = delete;
	D(const char *const pName, std::future<void>& _threadFuture);

	void operator()();

// Data
	std::future<void>& threadFuture;
};

#endif

// ---  End of File ---
