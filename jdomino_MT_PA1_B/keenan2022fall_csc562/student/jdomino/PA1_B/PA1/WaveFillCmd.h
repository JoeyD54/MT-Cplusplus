#ifndef WAVE_FILL_REQUEST_CMD_H
#define WAVE_FILL_REQUEST_CMD_H

#include "Command.h"
#include "WaveBuffThread.h"
#include "CoordinatorThread.h"
#include "PlaybackThread.h"

class WaveFillCmd :public Command
{
public:
	WaveFillCmd(WaveBuffThread* p);

	WaveFillCmd() = delete;
	WaveFillCmd(const WaveFillCmd&) = delete;
	WaveFillCmd& operator = (const WaveFillCmd&) = delete;
	~WaveFillCmd() = default;

	virtual void Execute() override;
	virtual void ExecutePlay() override;
	virtual void ExecuteDead() override;

private:
	WaveBuffThread* pWave;
};

#endif

// --- End of File ---

