#include "WaveOutCallback.h"
#include "PlaybackThread.h"

void CALLBACK WaveOutCallback(HWAVEOUT woHandle, UINT msg, DWORD dwInstance, DWORD param1, DWORD param2)
{
	AZUL_UNUSED_VAR(woHandle);
	AZUL_UNUSED_VAR(param2);

	UserWavePlayer* pWavePlayer = (UserWavePlayer*)dwInstance;
	WAVEHDR* waveHdr = 0;
	WaveFillCmd* cmd;

	switch (msg)
	{
	case WOM_OPEN:
		Trace::out("open");
		break;

	case WOM_DONE:
		waveHdr = (WAVEHDR*)param1;

		pWavePlayer->numWaves--;

		//param1 is the buffer pointer
		//send the command to playback to tell the playback you're done - 
	

		//needs the playback queue 
		cmd = new WaveFillCmd((WaveBuffThread*)waveHdr->dwUser);
		PlaybackThread::getQueue().PushBack(cmd); //get more

		break;

	case WOM_CLOSE:
		pWavePlayer->closed = true;
		Trace::out("close");
		break;

	default:
		assert(false);
	}



}
