//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef STUDENT_BASE_SOLVER_H
#define STUDENT_BASE_SOLVER_H

// Algorithm & Maze generation - refactored and modified from material on the internet
//    Influenced by many different solvers and maze categories
//    Purpose of the maze is to create a concurrent problem set for C++ concurrency class
//    Maze solving algorithm and generators were derived from University of Maryland - Java Development

#include <exception>
#include "StudentMazeSolver.h"
#include "Position.h"
#include "Choice.h"

#include "SharedData.h"


#define VECTOR_RESERVE_SIZE 400000
#define TOP_FLAG 0x8 //bit to set when TOP thread goes over cell
#define BOT_FLAG 0x4 //bit to set when BOTTOM thread goes over cell

class StudentSolFoundSkip : public std::exception
{
public:

	StudentSolFoundSkip(Position _pos, Direction _from)
	{
		this->pos = _pos;
		this->from = _from;
	}

	Position pos;
	Direction from;
};

class StudentBaseSolver : public StudentMazeSolver
{
public:

	StudentBaseSolver(Maze* maze)
		: StudentMazeSolver(maze)
	{
		assert(maze);
	}

	Choice firstChoice(Position pos)
	{
		ListDirection Moves = pMaze->getMoves(pos);

		if (Moves.size() == 1)
		{
			Direction tmp = Moves.begin();
			return follow(pos, tmp);
		}
		else
		{
			Choice p(pos, Direction::Uninitialized, Moves);
			return p;
		}
	}

	Choice follow(Position at, Direction dir)
	{
		ListDirection Choices;
		Direction go_to = dir;
		Direction came_from = reverseDir(dir);
		at = at.move(go_to);

		do
		{
			if (at == (pMaze->getEnd()))
			{
				throw StudentSolFoundSkip(at, reverseDir(go_to));

			}
			if (at == (pMaze->getStart()))
			{
				throw StudentSolFoundSkip(at, reverseDir(go_to));
			}
			Choices = pMaze->getMoves(at);
			Choices.remove(came_from);

			if (Choices.size() == 1)
			{
				go_to = Choices.begin();
				at = at.move(go_to);
				came_from = reverseDir(go_to);
			}

		} while (Choices.size() == 1);

		Choice pRet(at, came_from, Choices);

		return pRet;
	}



	void markPath(std::list<Direction>* path)
	{
		try
		{
			Choice pChoice = firstChoice(pMaze->getStart());

			Position at = pChoice.at;
			std::list<Direction>::iterator iter = path->begin();
			while (iter != path->end())
			{
				pChoice = follow(at, *iter);
				iter++;
				at = pChoice.at;
			}
		}
		catch (StudentSolFoundSkip e)
		{
			AZUL_UNUSED_VAR(e);
		}
	}





};

#endif

//--- End of File ------------------------------
