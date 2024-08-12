#pragma once

#include "WaveOutCallback.h"

class WaveOutManager
{
	//singleton handling wave out init and destruction/unprepare
public:
	~WaveOutManager();
	WaveOutManager(const WaveOutManager&) = delete;
	WaveOutManager& operator = (const WaveOutManager&) = delete;

	static HWAVEOUT& GetHandle();

private:
	WaveOutManager();
	static WaveOutManager& priGetInstance();

	UserWavePlayer wavePlayer;
	HWAVEOUT woHandle;

};



