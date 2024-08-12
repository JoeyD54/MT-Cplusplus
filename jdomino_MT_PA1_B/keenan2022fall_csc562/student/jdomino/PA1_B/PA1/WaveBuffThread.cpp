#include "WaveBuffThread.h"
#include "WaveOutManager.h"
#include "WaveFillCmd.h"
#include "KillEventWrapper.h"


WaveBuffThread::WaveBuffThread(const char* const pName, KillShare& _kill_var)
	:ThreadBase(pName, _kill_var), 
	poWaveBuff(WaveBuffThread::BUFFER_SIZE), 
	WOManHandle(WaveOutManager::GetHandle()),
	waveHdr{ 0 }
{

	//wave buffer controls its header and its data
	waveHdr.dwBufferLength = poWaveBuff.GetTotalSize();
	waveHdr.lpData = (char*)poWaveBuff.GetRawBuff();
	waveHdr.dwUser = (DWORD_PTR)this;

	MMRESULT result;
	result = waveOutPrepareHeader(WOManHandle, &waveHdr, sizeof(WAVEHDR));


	if (result != MMSYSERR_NOERROR)
	{
		Trace::out("**ERROR** - Wave out prepare");
		assert(false);
	}
}


WaveBuffThread::~WaveBuffThread()
{
	Debug::out("~WaveBuffThread()  join \n");
	MMRESULT result;
	result = waveOutUnprepareHeader(WOManHandle, &waveHdr, sizeof(WAVEHDR));
}

void WaveBuffThread::operator()()
{
	START_BANNER

	//Shut up compiler
}



void WaveBuffThread::FillBuffer(unsigned char* poBuff, size_t size)
{
	std::lock_guard<std::mutex> mlock(poWaveBuff.GetMutex());
	memcpy_s(poWaveBuff.GetRawBuff(), poWaveBuff.GetTotalSize(), poBuff, size);
	poWaveBuff.SetCurrSize(size);
}



void WaveBuffThread::TransferToWaveOut()
{
	MMRESULT result;
	result = waveOutWrite(WOManHandle, &waveHdr, sizeof(WAVEHDR));

	if (result != MMSYSERR_NOERROR)
	{
		Trace::out("**ERROR** - Wave out write");
		assert(false);
	}
}



//function
//send fill status
	//send command to playback queue
	// 
	// 
//