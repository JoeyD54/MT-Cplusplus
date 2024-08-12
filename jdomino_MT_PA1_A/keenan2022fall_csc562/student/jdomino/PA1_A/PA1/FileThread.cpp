//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <conio.h>

#include "FileThread.h"
#include "FileSlow.h"

FileThread* FileThread::pInstance = nullptr;

FileThread::FileThread(const char* const pName, std::future<void>& _tFuture, FileCoorShare& _share_fc)
	: BannerBase(pName),
	poBuff(new Buffer(FileThread::BUFFER_SIZE)),
	poFileName(new char[FileThread::FILE_NAME_SIZE]()),
	numFilesRead(0),
	share_fc(_share_fc),
	tFuture(_tFuture)
{
	assert(poBuff);
	assert(poFileName);

	share_fc.status = FileCoorShare::Status::Empty;

	assert(FileThread::pInstance == nullptr);

	FileThread::pInstance = this;
}


void FileThread::operator()()
{
	START_BANNER

		while (true)
		{
			{  // needs to be protected by scope... 
			   // sometimes it gets a lock and status is not empty
			   // someone needs to unlock it
				std::unique_lock<std::mutex> lck(share_fc.mtx);
				if (share_fc.status == FileCoorShare::Status::Empty)
				{
					lck.unlock();  // <-- do not hold during load otherwise stall Coord thread
					if (this->numFilesRead < FileThread::MAX_NUM_FILES)
					{
						int i = this->numFilesRead;
						char* pName = this->privGetFileName(i);
						this->privLoadFile(pName);

						std::unique_lock<std::mutex> lck(share_fc.mtx);
						share_fc.status = FileCoorShare::Status::Ready;

						share_fc.cv.notify_one();
					}
				}
			}

			std::this_thread::sleep_for(200ms);

			//std::future_status killStatus = this->tFuture.wait_for(0ms);
			//if (killStatus == std::future_status::ready)
			//{
			//	break;
			//}
		}
}

void FileThread::privLoadFile(const char* const pFileName)
{
	FileSlow::Handle fh;
	FileSlow::Error err;

	assert(pFileName);

	Debug::out("%s load start <-- \n", pFileName);

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

	Debug::out("%s load end --> %d bytes \n", pFileName, poBuff->GetCurrSize());
}

char* FileThread::privGetFileName(int index)
{
	sprintf_s(poFileName, FileThread::FILE_NAME_SIZE, "wave_%d.wav", index);
	return poFileName;
}

FileThread::~FileThread()
{
	Debug::out("~FileThread()  join \n");
	//need to stop the thread first due to buffer memory
	
	if (this->mThread.joinable())
	{
		this->mThread.join();
	}

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

void FileThread::Launch()
{
	if (this->mThread.joinable() == false)
	{
		this->mThread = std::thread(std::ref(*this));
	}
	else
	{
		assert(false);
	}
}