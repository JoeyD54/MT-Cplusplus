//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef C_H

using namespace ThreadFramework;

class C : public BannerBase
{
public:
	C() = delete;
	C(const char *const pName, std::future<void>& _threadFuture);

	void operator()();

// Data
	std::future<void>& threadFuture;
};

#endif

// ---  End of File ---
