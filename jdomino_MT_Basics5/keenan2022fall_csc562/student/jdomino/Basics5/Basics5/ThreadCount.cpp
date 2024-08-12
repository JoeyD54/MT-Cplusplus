//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadCount.h"

ThreadCount::ThreadCount()
{
    ThreadCountProxy::Increment();
}


ThreadCount::~ThreadCount()
{
    ThreadCountProxy::Decrement();
}

// ---  End of File ---
