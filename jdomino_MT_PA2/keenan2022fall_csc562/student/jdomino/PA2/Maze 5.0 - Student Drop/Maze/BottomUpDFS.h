
#ifndef BOTTOM_UP_DFS_H
#define BOTTOM_UP_DFS_H

// Algorithm & Maze generation - refactored and modified from material on the internet
//    Influenced by many different solvers and maze categories
//    Purpose of the maze is to create a concurrent problem set for C++ concurrency class
//    Maze solving algorithm and generators were derived from University of Maryland - Java Development

#include <list>
#include <vector>

#include "Choice.h"
#include "StudentBaseSolver.h"

class BottomUpDFS : public StudentBaseSolver
{
public:
	BottomUpDFS(Maze* maze, std::vector<Direction>* pHalfSolve, SharedData& _sd)
		: StudentBaseSolver(maze), phalfSol(*pHalfSolve), sd(_sd)
	{
		assert(pMaze);
		//positions = new std::vector<Position>();
	}

	void operator()()
	{
		std::vector<Choice> pChoiceStack;
		pChoiceStack.reserve(VECTOR_RESERVE_SIZE);  // Optimized allocations...

		Choice ch;
		try
		{
			pChoiceStack.push_back(firstChoice(pMaze->getEnd()));
			//positions->push_back(pMaze->getEnd()); //pop start position onto positions
			positions[posIndex] = pMaze->getEnd();
			posIndex++;

			while (!(pChoiceStack.size() == 0) && sd.done != true)//while we can still go and the other thread hasn't flipped done flag
			{
				ch = pChoiceStack.back();

				if (ch.isDeadend())
				{
					pChoiceStack.pop_back();

					//while the postion row
					while (positions[posIndex-1].col != pChoiceStack.back().at.col || positions[posIndex-1].row != pChoiceStack.back().at.row)
					{
						posIndex--; //go back until we are back on track with choices
					}
					
					if (!(pChoiceStack.size() == 0))
					{
						pChoiceStack.back().pChoices.pop_front();
					}
					continue;
				}

				//not dead end
				pMaze->poMazeData[ch.at.row * pMaze->width + ch.at.col].fetch_or(BOT_FLAG);
				if  ( (pMaze->poMazeData[ch.at.row * pMaze->width + ch.at.col] & TOP_FLAG) == TOP_FLAG)
				{
					//Trace::out("collision in BOT");
					sd.done = true;
					sd.endPos = ch.at; //update position
					throw StudentSolFoundSkip(ch.at, ch.from);
					break;
					
				}

				pChoiceStack.push_back(follow(ch.at, ch.pChoices.front()));

			}
			// No solution found.
			//return 0;
			throw StudentSolFoundSkip(ch.at, ch.from);
		}
		catch (StudentSolFoundSkip e)
		{
			AZUL_UNUSED_VAR(e); // unused


			//while (positions->back().col != sd.endPos.col || positions->back().row != sd.endPos.row)
			//{
			//	positions->pop_back(); //get rid of end until we are at the end 
			//}

			//std::vector<Position>::const_iterator toCompare = positions->begin();
			//std::vector<Position>::const_iterator i;
			for (int i = 0; i < posIndex; i++)
			{				//toCompare = i++;
				//Trace::out("Row: %d, Col:%d\n", i->row, i->col);
				//if (positions[posIndex].row != sd.endPos.row && positions[posIndex].col != sd.endPos.col) //if the next is not the end - will figure this one out
				if (i + 1 != posIndex)
				{
					if (positions[i].row == sd.endPos.row && positions[i].col == sd.endPos.col)
					{
						break;
					}

					Position toCompare = positions[i + 1];

					if (positions[i].row - toCompare.row < 0)
					{
						//went south
						phalfSol.push_back(Direction::North);
						std::rotate(phalfSol.rbegin(), phalfSol.rbegin() + 1, phalfSol.rend());
						//Trace::out(DirectionHelper::getString(Direction::North));
					}
					else if (positions[i].row - toCompare.row > 0)
					{
						//went north
						phalfSol.push_back(Direction::South);
						std::rotate(phalfSol.rbegin(), phalfSol.rbegin() + 1, phalfSol.rend());
						//Trace::out(DirectionHelper::getString(Direction::South));
					}
					else if (positions[i].col - toCompare.col < 0)//row is the same, check col now
					{
						//went east
						phalfSol.push_back(Direction::West);
						std::rotate(phalfSol.rbegin(), phalfSol.rbegin() + 1, phalfSol.rend());
						//Trace::out(DirectionHelper::getString(Direction::West));
					}
					else if (positions[i].col - toCompare.col > 0)//row is the same, check col now
					{
						//went west
						phalfSol.push_back(Direction::East);
						std::rotate(phalfSol.rbegin(), phalfSol.rbegin() + 1, phalfSol.rend());
						//Trace::out(DirectionHelper::getString(Direction::West));
					}
				}
			}
			//delete positions;
			
		}
	}




	Choice follow(Position at, Direction dir)  //throws SolutionFoundSkip() 
	{
		ListDirection Choices;
		Direction go_to = dir;
		Direction came_from = reverseDir(dir);
		at = at.move(go_to);

		positions[posIndex] = at; //push position into vector
		posIndex++;

		pMaze->poMazeData[at.row * pMaze->width + at.col].fetch_or(BOT_FLAG); //paint path
		do
		{
			if (at == (pMaze->getStart()))
			{
				throw StudentSolFoundSkip(at, reverseDir(go_to));
			}
			if (at == (pMaze->getEnd()))
			{
				throw StudentSolFoundSkip(at, reverseDir(go_to));

			}
			Choices = pMaze->getMoves(at);
			Choices.remove(came_from);

			if (Choices.size() == 1)
			{
				go_to = Choices.begin();
				at = at.move(go_to);
				positions[posIndex] = at; //push position into vector
				posIndex++;
				pMaze->poMazeData[at.row * pMaze->width + at.col].fetch_or(BOT_FLAG); //paint path
				came_from = reverseDir(go_to);
			}

		} while (Choices.size() == 1);

		Choice pRet(at, came_from, Choices);

		return pRet;
	}


	//--DATA--//
	//std::vector<Position>* positions;
	Position positions[60000];
	int posIndex = 0;

	std::vector<Direction>& phalfSol;

	//std::atomic_bool& done;
	SharedData& sd;
};




#endif

//--- End of File ------------------------------
