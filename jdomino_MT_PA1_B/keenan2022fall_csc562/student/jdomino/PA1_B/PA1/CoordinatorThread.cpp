//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <conio.h>

#include "CoordinatorThread.h"
#include "FileThread.h"
#include "KillEventWrapper.h"
#include "Command.h"
#include "PlaybackThread.h"

CoordinatorThread* CoordinatorThread::pInstance = nullptr;

CoordinatorThread::CoordinatorThread(const char* const pName, KillShare& _kill_var, FileCoordShare& _share_fc, CircularData& CoordInQueue)
	: ThreadBase(pName, _kill_var),
	share_fc(_share_fc),
	pBuff_A(new Buffer(CoordinatorThread::BUFFER_SIZE)),
	pBuff_B(new Buffer(CoordinatorThread::BUFFER_SIZE)),
	pFillBuffer(nullptr),
	pDrainBuffer(pBuff_A),
	currentBuffFlag(true),
	inQueue(CoordInQueue),
	status(Status::CoordThreadBuffer_Not_Ready)
{
	assert(pBuff_A);
	assert(pBuff_B);

	CoordinatorThread::pInstance = this;
}


void CoordinatorThread::operator()()
{
	START_BANNER
	KillEventSetup

	Command* pCmd;
	while (!KillEvent())
	{
		//Scope this to help keep thread safe. Unlocks on exit
		{      
			std::unique_lock<std::mutex> lck(share_fc.mtx);
			if (share_fc.cv.wait_for(lck, 0ms, [&]() { return (share_fc.status == FileCoordShare::Status::FileThreadBufferReady
														|| share_fc.status == FileCoordShare::Status::DONE); }))
			{		
				if (share_fc.status == FileCoordShare::Status::DONE)
				{
					//We're done, but buffer is not empty.
				}
				else 
				{
					if (this->pBuff_A->status == BufferStatus::EMTPY)
					{
						this->pFillBuffer = pBuff_A;
						share_fc.status = FileCoordShare::Status::FileThreadBufferTransfering;
					}
					else if (this->pBuff_B->status == BufferStatus::EMTPY)
					{
						this->pFillBuffer = pBuff_B;
						share_fc.status = FileCoordShare::Status::FileThreadBufferTransfering;
					}
				}
			}
			//need this
			lck.unlock();	
		}

		//Copy data into pFillBuffer
		if (share_fc.status == FileCoordShare::Status::FileThreadBufferTransfering)
		{
			FileThread::CopyBuffer(this->pFillBuffer);

			status = Status::CoordThreadBuffer_Ready;
			pFillBuffer->status = BufferStatus::FULL;
			share_fc.status = FileCoordShare::Status::FileThreadBufferEmpty;
		}

		//We're good, send to wave
		if (status == Status::CoordThreadBuffer_Ready)
		{
			if (inQueue.PopFront(pCmd))
			{
				pCmd->Execute();
			}
		}
	}
}


CoordinatorThread::~CoordinatorThread()
{
	Debug::out("~CoordThread()  join \n");

	//stop thread first
	ThreadBase::~ThreadBase();

	//then the buffers
	delete pBuff_A;
	pBuff_A = nullptr;

	delete pBuff_B;
	pBuff_B = nullptr;;

}

unsigned char* CoordinatorThread::GetNext2KBuff()
{
	CoordinatorThread& coordThread = CoordinatorThread::privGetInstance();

	if (coordThread.pDrainBuffer == nullptr) { return nullptr; }

	//find how much we have used out of buffer
	coordThread.bufferTag = coordThread.pDrainBuffer->GetRawBuff() + coordThread.pDrainBuffer->GetUsedSize();
	coordThread.pDrainBuffer->SetUsedSize(coordThread.pDrainBuffer->GetUsedSize() + 2048);

	if (coordThread.pDrainBuffer->GetUsedSize() >= coordThread.pDrainBuffer->GetCurrSize())
	{
		coordThread.pDrainBuffer->status = BufferStatus::EMTPY;
		Debug::out("  SWITCHED BUFFERS \n");

		if (coordThread.pDrainBuffer == coordThread.pBuff_A)
		{
			coordThread.pFillBuffer = coordThread.pBuff_A;
			coordThread.pDrainBuffer->SetUsedSize(0);
			coordThread.pDrainBuffer = coordThread.pBuff_B;	
		}
		else if (coordThread.pDrainBuffer == coordThread.pBuff_B)
		{
			coordThread.pFillBuffer = coordThread.pBuff_B;
			coordThread.pDrainBuffer->SetUsedSize(0);
			coordThread.pDrainBuffer = coordThread.pBuff_A;			
		}

		//if new drain is empty, the song is done
		if (coordThread.pDrainBuffer->status == BufferStatus::EMTPY)
		{
			//WRAP IT UP
			PlaybackThread::kill();
		}
	}
	return coordThread.bufferTag;
}

CoordinatorThread& CoordinatorThread::privGetInstance()
{
	return *pInstance;
}


// --- End of File ---
