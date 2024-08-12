#ifndef TOP_DOWN_DFS_VECTOR_H
#define TOP_DOWN_DFS_VECTOR_H

// Algorithm & Maze generation - refactored and modified from material on the internet
//    Influenced by many different solvers and maze categories
//    Purpose of the maze is to create a concurrent problem set for C++ concurrency class
//    Maze solving algorithm and generators were derived from University of Maryland - Java Development

#include <list>
#include <vector>

#include "Choice.h"
#include "StudentBaseSolver.h"

class TopDownDFSVector : public StudentBaseSolver
{
public:
	TopDownDFSVector(Maze* maze, std::vector<Direction>* pHalfSolve, SharedData& _sd)
		: StudentBaseSolver(maze), phalfSol(*pHalfSolve), sd(_sd)
	{
		assert(pMaze);
	}


	void operator()()

	{
		std::vector<Choice> pChoiceStack;
		pChoiceStack.reserve(VECTOR_RESERVE_SIZE);

		Choice ch;
		try
		{
			pChoiceStack.push_back(firstChoice(pMaze->getStart()));

			//Not done and there's more decisions, keep going
			while (!(pChoiceStack.size() == 0) && sd.done != true) 
			{
				ch = pChoiceStack.back();	

				if (ch.isDeadend())
				{
					pChoiceStack.pop_back();

					if (!(pChoiceStack.size() == 0))
					{
						//No list, just take the top
						pChoiceStack.back().pChoices.pop_front();
					}

					continue;
				}

				//We're not dead, say we were here and move on		
				pMaze->poMazeData[ch.at.row * pMaze->width + ch.at.col].fetch_or(TOP_FLAG);

				if ((pMaze->poMazeData[ch.at.row * pMaze->width + ch.at.col] & BOT_FLAG) == BOT_FLAG)
				{
					// A was set: collision
					sd.done = true;
					sd.endPos = ch.at;
					throw StudentSolFoundSkip(ch.at, ch.from);
					break;
				}
				pChoiceStack.push_back(follow(ch.at, ch.pChoices.front()));

			}
			//break and leave
			throw StudentSolFoundSkip(ch.at, ch.from);
		}
		catch (StudentSolFoundSkip e)
		{
			AZUL_UNUSED_VAR(e); // unused

			std::vector<Choice>::iterator iter = pChoiceStack.begin();
			Position curr = pMaze->getStart();
			Direction go_to = Direction::Uninitialized;
			Direction came_from = Direction::Uninitialized;

			while (!(curr.row == sd.endPos.row && curr.col == sd.endPos.col))
			{
				ListDirection pMoves = pMaze->getMoves(curr);

				if (Direction::Uninitialized != came_from)
				{
					pMoves.remove(came_from);
				}

				if (pMoves.size() == 1)
				{
					go_to = pMoves.front();
				}
				else if (pMoves.size() > 1)
				{
					go_to = iter++->pChoices.front();
				}
				else if (pMoves.size() == 0)
				{
					printf("Error in solution--leads to deadend.");
					assert(false);
				}

				phalfSol.push_back(go_to);
				curr = curr.move(go_to);
				came_from = reverseDir(go_to);
			}
		}
	}


	Choice follow(Position at, Direction dir)
	{
		ListDirection Choices;
		Direction go_to = dir;
		Direction came_from = reverseDir(dir);
		at = at.move(go_to);

		pMaze->poMazeData[at.row * pMaze->width + at.col].fetch_or(TOP_FLAG);
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
				pMaze->poMazeData[at.row * pMaze->width + at.col].fetch_or(TOP_FLAG);
				came_from = reverseDir(go_to);
			}

		} while (Choices.size() == 1);

		Choice pRet(at, came_from, Choices);
		return pRet;
	}

	//------------
	// Data
	//------------
	std::vector<Direction>& phalfSol;
	SharedData& sd;
};

#endif

//--- End of File ------------------------------

