//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_H

using namespace ThreadFramework;

class A : public BannerBase
{
public:
	A() = delete;
	A(const char* const pName, std::future<void>& _threadFuture);

	void operator()();

// Data
	std::future<void> &threadFuture;

};

#endif

// ---  End of File ---