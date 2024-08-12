//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <conio.h>

//-------------------------------------------------------------
//  ADD work here in this file
//  Modify any *.h or *.cpp
//  No Globals allowed
//  Make sure these threads close cleanly with the getchar
//-------------------------------------------------------------

#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"
#include "Controller.h"
#include "ThreadCount.h"
#include "SharedData.h"

void SimulatedMain()
{
	SimpleBanner b;	

	std::promise<void> threadPromise;
	std::future<void> threadFuture = threadPromise.get_future();

	// Create Objects
	A oA("A", threadFuture);
	B oB("B", threadFuture);
	C oC("C", threadFuture);
	D oD("D", threadFuture);
	Controller oController("Controller");

	// Spawn threads 

	// ALL Threads:
	//   Need to be "detach/async" in nature
	//   You cannot use join() on any threads


	std::thread tA(oA);
	std::thread tB(oB);
	std::thread tC(oC);
	std::thread tD(oD);

	std::future<void> futureController = async(std::launch::async, 
											   std::ref(oController),
											   std::ref(threadPromise));	

	tA.detach();
	tB.detach();
	tC.detach();
	tD.detach();

	oController.getKeyPress();

	// Key press, need to keep this, key is triggered in unit test
	//_getch();   // <--- needs a key press to trigger
                    //      work is done inside controller
                    //      no sleeping to synchronizing exit conditions

	// Unit test is verifying that you have a clean exit

	futureController.get();
}

// ---  End of File ---

