#include "WaveOutManager.h"

WaveOutManager::WaveOutManager()
	: wavePlayer(), woHandle{0}
{
	MMRESULT result;
	WAVEFORMATEX waveFormat;

	waveFormat.nSamplesPerSec = 22050;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nBlockAlign = (DWORD)(waveFormat.wBitsPerSample >> 3) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nBlockAlign * waveFormat.nSamplesPerSec;
	waveFormat.cbSize = 0;

	result = waveOutOpen(&woHandle, WAVE_MAPPER, &waveFormat, (DWORD)&WaveOutCallback, (DWORD)&wavePlayer, CALLBACK_FUNCTION);

	float v = 0.5f; //both channels
	unsigned short left = unsigned short(0xFFFF * v);
	unsigned short right = unsigned short(0xFFFF * v);
	unsigned long x = (unsigned long) (left + (right << 16));
	waveOutSetVolume(woHandle, x);

	if (result != MMSYSERR_NOERROR)
	{
		Trace::out("error w/ wave out open");
		assert(false);
	}
}

WaveOutManager::~WaveOutManager()
{
	MMRESULT result;
	result = waveOutClose(woHandle);
}

HWAVEOUT& WaveOutManager::GetHandle()
{
	WaveOutManager& temp = WaveOutManager::priGetInstance();
	return temp.woHandle;
}

WaveOutManager& WaveOutManager::priGetInstance()
{
	static WaveOutManager temp;
	return temp;
}
