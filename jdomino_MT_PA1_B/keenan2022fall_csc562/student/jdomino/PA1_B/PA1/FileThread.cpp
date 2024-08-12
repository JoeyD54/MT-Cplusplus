//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <conio.h>

#include "FileThread.h"
#include "KillEventWrapper.h"
#include "FileSlow.h"

FileThread* FileThread::pInstance = nullptr;

FileThread::FileThread(const char* const pName, KillShare& _kill_var, FileCoordShare& _share_fc)
	: ThreadBase(pName, _kill_var),
	poBuff(new Buffer(FileThread::BUFFER_SIZE)),
	poFileName(new char[FileThread::FILE_NAME_SIZE]()),
	numFilesRead(0),
	share_fc(_share_fc)
{
	assert(poBuff);
	assert(poFileName);

	share_fc.status = FileCoordShare::Status::FileThreadBufferEmpty;

	assert(FileThread::pInstance == nullptr);

	FileThread::pInstance = this;
}


void FileThread::operator()()
{
	START_BANNER
		KillEventSetup

		while (!KillEvent())
		{
			{  // protected by scope. forces unlock on exit			   
				std::unique_lock<std::mutex> lck(share_fc.mtx);
				if (share_fc.status == FileCoordShare::Status::FileThreadBufferEmpty)
				{
					lck.unlock();
					if (this->numFilesRead < FileThread::MAX_NUM_WAVE_FILES)
					{
						int i = this->numFilesRead;
						char* pName = this->privGetFileName(i);
						this->privLoadFile(pName);

						std::unique_lock<std::mutex> lck2(share_fc.mtx);
						share_fc.status = FileCoordShare::Status::FileThreadBufferReady;
						lck2.unlock();
						share_fc.cv.notify_one();
					}
					else if (this->numFilesRead == FileThread::MAX_NUM_WAVE_FILES)
					{
						{
							std::unique_lock<std::mutex> lck2(share_fc.mtx);
							share_fc.status = FileCoordShare::Status::DONE;
							lck2.unlock();
							share_fc.cv.notify_one();
							this->numFilesRead++;
						}
					}
				}
			}
			std::this_thread::sleep_for(200ms);
		}
}

void FileThread::privLoadFile(const char* const pFileName)
{
	FileSlow::Handle fh;
	FileSlow::Error err;

	assert(pFileName);

	err = FileSlow::Open(fh, pFileName, FileSlow::Mode::READ);
	assert(err == FileSlow::Error::SUCCESS);

	err = FileSlow::Seek(fh, FileSlow::Location::END, 0);
	assert(err == FileSlow::Error::SUCCESS);

	DWORD size;
	err = FileSlow::Tell(fh, size);
	assert(err == FileSlow::Error::SUCCESS);

	err = FileSlow::Seek(fh, FileSlow::Location::BEGIN, 0);
	assert(err == FileSlow::Error::SUCCESS);

	err = FileSlow::Read(fh, poBuff->GetRawBuff(), size);
	assert(err == FileSlow::Error::SUCCESS);

	err = FileSlow::Close(fh);
	assert(err == FileSlow::Error::SUCCESS);

	poBuff->SetCurrSize(size);

	this->numFilesRead++;
}

char* FileThread::privGetFileName(int index)
{
	sprintf_s(poFileName, FileThread::FILE_NAME_SIZE, "wave_%d.wav", index);
	return poFileName;
}

FileThread::~FileThread()
{
	Debug::out("~FileThread()  join \n");
	
	//stop thread first.
	ThreadBase::~ThreadBase();

	//Then the buffers
	delete poBuff;
	poBuff = nullptr;

	delete poFileName;
	poFileName = nullptr;
}

FileThread& FileThread::privGetInstance()
{
	assert(FileThread::pInstance);
	return *pInstance;
}

size_t FileThread::CopyBuffer(Buffer* pDest)
{
	assert(pDest);
	FileThread& r = FileThread::privGetInstance();

	if (r.poBuff != nullptr)
	{
		std::lock_guard<std::mutex> lock(r.poBuff->GetMutex());
		memcpy_s(pDest->GetRawBuff(), pDest->GetTotalSize(), r.poBuff->GetRawBuff(), r.poBuff->GetCurrSize());
		pDest->SetCurrSize(r.poBuff->GetCurrSize());

	}
	return pDest->GetCurrSize();
}

