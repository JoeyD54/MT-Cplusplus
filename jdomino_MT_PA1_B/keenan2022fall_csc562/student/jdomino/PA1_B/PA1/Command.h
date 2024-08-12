//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	virtual void Execute() = 0;
	virtual void ExecutePlay() = 0;
	virtual void ExecuteDead() = 0;
};

#endif

// --- End of File ---

