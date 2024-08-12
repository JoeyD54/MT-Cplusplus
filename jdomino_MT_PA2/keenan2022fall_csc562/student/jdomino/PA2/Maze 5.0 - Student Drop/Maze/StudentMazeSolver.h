//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef STUDENT_MAZE_SOLVER_H
#define STUDENT_MAZE_SOLVER_H

#include <list>
#include <vector>

#include "Maze.h"

class StudentMazeSolver
{

public:
	// Constructor, set the maze
	StudentMazeSolver(Maze* maze)
	{
		pMaze = maze;
		assert(this->pMaze);
	}

protected:
	// data
	Maze* pMaze;

};

#endif

//--- End of File ------------------------------
