//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef PLAYBACK_THREAD_H
#define PLAYBACK_THREAD_H

#include "ThreadBase.h"
#include "CircularData.h"
#include "WaveBuffThread.h"
#include "WaveFillCmd.h"


struct KillShare;

class PlaybackThread : public ThreadBase
{
public:
	static const unsigned int BUFFER_SIZE = 512 * 1024;

public:
	PlaybackThread(const char* const pName,
		KillShare& _kill_var, CircularData& CoordInqueue);

	PlaybackThread() = delete;
	PlaybackThread(const PlaybackThread&) = delete;
	PlaybackThread& operator = (const PlaybackThread&) = delete;
	~PlaybackThread();

	void operator()() override;

	static bool getKillStatus();
	static void kill();
	static CircularData& getQueue();
	static void Increment(WaveBuffThread* wave);
	static void Decrement();
	void Play();

private:
	// --------------------------
	// Data
	// --------------------------
	static PlaybackThread* pInstance;

	CircularData& inQueue;
	static PlaybackThread& privGetInstance();
	WaveBuffThread* pWaveThreads[20];
	CircularData playQueue;

	int waveCount = 0;
	bool playing;
	bool killPlay;
};

#endif

// --- End of File ---
