// ----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WaveFillCmd.h"


using namespace ThreadFramework;

WaveFillCmd::WaveFillCmd(WaveBuffThread* p)
	: pWave(p)
{
	assert(p);
}


void WaveFillCmd::Execute()
{
	if (PlaybackThread::getKillStatus())
	{
		PlaybackThread::Decrement();
		delete this;
	} 
	else
	{
		unsigned char* pDest = CoordinatorThread::GetNext2KBuff();

		if (pDest != nullptr)
		{
			pWave->FillBuffer(pDest, 2 * 1024);
			PlaybackThread::Increment(pWave);
		}

		delete this;
	}
}

void WaveFillCmd::ExecutePlay()
{
	pWave->TransferToWaveOut();
	delete this;
}

void WaveFillCmd::ExecuteDead()
{
	delete this;
}


// --- End of File ---