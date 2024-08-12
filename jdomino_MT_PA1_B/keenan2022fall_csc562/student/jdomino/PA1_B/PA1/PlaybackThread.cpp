//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <conio.h>

#include "PlaybackThread.h"
#include "KillEventWrapper.h"

PlaybackThread* PlaybackThread::pInstance = nullptr;

PlaybackThread::PlaybackThread(const char* const pName,
	KillShare& _kill_var, CircularData& CoordInqueue)
	: ThreadBase(pName, _kill_var),
	inQueue(CoordInqueue),
	waveCount(0),
	playing(false),
	killPlay(false)
{
	pInstance = this;

	for (int i = 0; i < 20; i++)
	{
		WaveBuffThread* pWaveInstance = new WaveBuffThread("--wave--", this->getKill());
		pWaveThreads[i] = pWaveInstance;

		pWaveInstance->Launch();
	}

	for (int i = 0; i < 20; i++)
	{
		WaveFillCmd* pCmd = new WaveFillCmd(pWaveThreads[i]);
		inQueue.PushBack(pCmd);
	}

}

void PlaybackThread::operator()()
{
	START_BANNER

	Command* pCmd;

	while (!killPlay)
	{ 
		if (playing)
		{
			//Play if we have something
			if (playQueue.PopFront(pCmd))
			{
				pCmd->ExecutePlay();
			}
		}
	}

	while (playing) 
	{
		//Keep playing if we have something
		if (playQueue.PopFront(pCmd))
		{
			pCmd->ExecutePlay();
		}
	}
}

bool PlaybackThread::getKillStatus()
{
	PlaybackThread& r = privGetInstance();
	return r.killPlay;
}

void PlaybackThread::kill()
{
	PlaybackThread& r = privGetInstance();
	r.killPlay = true;
}

void PlaybackThread::Increment(WaveBuffThread* wave)
{
	PlaybackThread& r = privGetInstance();

	if (r.playing)
	{
		WaveFillCmd* cmd = new WaveFillCmd(wave);

		//Push play to end of queue
		r.playQueue.PushBack(cmd);
		return;		
	}
	else
	{
		r.waveCount++;
		Trace::out("waveCount++ is %d\n", r.waveCount);
		if (r.waveCount == 20)
		{
			r.playing = true;
			r.Play();
		}
	}
}

void PlaybackThread::Play()
{
	for (int i = 0; i < 20; i++)
	{
		pWaveThreads[i]->TransferToWaveOut();
	}
}

void PlaybackThread::Decrement()
{
	PlaybackThread& r = privGetInstance();
	r.waveCount--;
	Trace::out("waveCount-- is %d\n", r.waveCount);

	if (r.waveCount == 0)
	{
		Trace::out("KILLED");
		r.playing = false;
		r.getKill().prom.set_value();

		for (int i = 0; i < 20; i++)
		{
			//Clear out what we don't need or else leak
			delete r.pWaveThreads[i];
		}
	}
}

PlaybackThread::~PlaybackThread()
{
	Debug::out("~PlaybackThread()  join \n");
	Debug::out("~PlaybackThread()  execute more? \n");

	ThreadBase::~ThreadBase();
}

PlaybackThread& PlaybackThread::privGetInstance()
{
	return *pInstance;
}

CircularData& PlaybackThread::getQueue()
{
	PlaybackThread& r = privGetInstance();
	return r.inQueue;
}


// --- End of File ---
