#pragma once
#include "WaveFillCmd.h"

struct UserWavePlayer
{
	UserWavePlayer()
	{
		this->donePlaying = false;
		this->closed = false;
		this->numWaves = 4;
	}

	bool donePlaying;
	bool closed;
	volatile int numWaves;
};

void CALLBACK WaveOutCallback(HWAVEOUT woHandle, UINT msg, DWORD dwInstance, DWORD param1, DWORD param2);