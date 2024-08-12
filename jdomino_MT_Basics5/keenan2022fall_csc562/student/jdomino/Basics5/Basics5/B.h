//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef B_H

using namespace ThreadFramework;

class B : public BannerBase
{
public:
	B() = delete;
	B(const char *const pName, std::future<void>& _threadFuture);

	void operator()();

// Data
	std::future<void>& threadFuture;
};

#endif

// ---  End of File ---
