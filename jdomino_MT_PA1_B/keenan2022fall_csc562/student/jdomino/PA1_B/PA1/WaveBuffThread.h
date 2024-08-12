#pragma once


#ifndef WAVE_BUFF_THREAD_H
#define WAVE_BUDD_THREAD_H

#include "ThreadBase.h"
#include "Buffer.h"

class WaveBuffThread : public ThreadBase
{

public:

	static const unsigned int BUFFER_SIZE = 2 * 1024;

	WaveBuffThread(const char* const pName, KillShare& _kill_var);
	~WaveBuffThread();

	//big four
	WaveBuffThread() = delete;
	WaveBuffThread(const WaveBuffThread&) = delete;
	WaveBuffThread& operator = (const WaveBuffThread&) = delete;

	void operator()() override;
	void FillBuffer(unsigned char* pBuff, size_t size);
	void TransferToWaveOut();

	//-----------
	// Data
	//-----------

	Buffer poWaveBuff;
	HWAVEOUT& WOManHandle;
	WAVEHDR waveHdr;

private:
	bool Full = false;
};


#endif


