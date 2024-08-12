
#ifndef MT_Maze_Student_Solver_H
#define MT_Maze_Student_Solver_H

#include <list>
#include <vector>
#include "Maze.h"
#include "Direction.h"

#include "StudentMazeSolver.h"
#include "SharedData.h"
#include "BottomUpDFS.h"
#include "TopDownDFS.h"
#include "TopDownDFSVector.h"
#include "BottomUpDFSVector.h"

// Feel free to change your class any way you see fit
// It needs to inherit at some point from the MazeSolver
class MTMazeStudentSolver : public StudentMazeSolver 
{
public:
	enum SearchType
	{
		ARRAY,
		VECTOR
	};
public: 
	MTMazeStudentSolver(Maze *maze, SearchType _type) 
	: StudentMazeSolver( maze ), type(_type)
	{
		assert(pMaze);
		
	}

	std::vector<Direction> *Solve() 
	{
		// Do your magic here
		std::vector<Direction>* firstHalf = new std::vector<Direction>();
		firstHalf->reserve(VECTOR_RESERVE_SIZE);
		std::vector<Direction>* secondHalf = new std::vector<Direction>();
		SharedData sd;

		//SharedData sd;
		if (type == SearchType::ARRAY)
		{
			Trace::out("Array solver");
			TopDownDFS TDSolver(pMaze, firstHalf, sd);
			BottomUpDFS BUSolver(pMaze, secondHalf, sd);


			std::thread tA(TDSolver);
			std::thread tB(BUSolver);

			tA.join();
			tB.join();

			firstHalf->insert(firstHalf->end(), secondHalf->begin(), secondHalf->end());

			//return combined list
			delete secondHalf;
		}
		else if (type == SearchType::VECTOR)
		{
			Trace::out("Vector solver\n");
			TopDownDFSVector TDSolver(pMaze, firstHalf, sd);
			BottomUpDFSVector BUSolver(pMaze, secondHalf, sd);


			std::thread tA(TDSolver);
			std::thread tB(BUSolver);

			tA.join();
			tB.join();

			firstHalf->insert(firstHalf->end(), secondHalf->begin(), secondHalf->end());

			//return combined list
			delete secondHalf;

		}

		return firstHalf;
	}
	



	void TopDownDirections(std::vector<Position>* topPositions, std::vector<Direction>* direction )
	{
		std::vector<Position>::const_iterator toCompare = topPositions->begin();
		std::vector<Position>::const_iterator i;
		for (i = topPositions->begin(); i != topPositions->end(); i++)
		{
			//Not the end? Where did we go?
			if (i + 1 != topPositions->end()) 
			{
				toCompare = i + 1;
				if (i->row - toCompare->row < 0)
				{
					//went south
					direction->push_back(Direction::South);
				}
				else if (i->row - toCompare->row > 0)
				{
					//went north
					direction->push_back(Direction::North);
				}
				else if (i->col - toCompare->col < 0)
				{
					//went east
					direction->push_back(Direction::East);
				}
				else if (i->col - toCompare->col > 0)
				{
					//went west
					direction->push_back(Direction::West);
				}
			}
		}
	}

	void BotDownDirections(std::vector<Position>* Positions, std::vector<Direction>* temp)
	{
		std::vector<Position>::const_iterator toCompare = Positions->begin();
		std::vector<Position>::const_iterator i;

		for (i = Positions->begin(); i != Positions->end(); i++)
		{
			//Are we at end? Where did we go?
			//Flip the direction to print properly
			if (i + 1 != Positions->end()) 
			{
				toCompare = i + 1;
				if (i->row - toCompare->row < 0)
				{
					//went south
					temp->push_back(Direction::North);
					std::rotate(temp->rbegin(), temp->rbegin() + 1, temp->rend());
				}
				else if (i->row - toCompare->row > 0)
				{
					//went north
					temp->push_back(Direction::South);
					std::rotate(temp->rbegin(), temp->rbegin() + 1, temp->rend());
				}
				else if (i->col - toCompare->col < 0)
				{
					//went east
					temp->push_back(Direction::West);
					std::rotate(temp->rbegin(), temp->rbegin() + 1, temp->rend());
				}
				else if (i->col - toCompare->col > 0)
				{
					//went west
					temp->push_back(Direction::East);
					std::rotate(temp->rbegin(), temp->rbegin() + 1, temp->rend());
				}
			}
		}
	}

	Direction Opposite(Direction go_to)
	{
		Direction toReturn = Direction::Uninitialized;
		switch (go_to)
		{
		case Direction::East:
			toReturn = Direction::West;
			break;
		case Direction::West:
			toReturn = Direction::East;
			break;
		case Direction::South:
			toReturn = Direction::North;
			break;
		case Direction::North:
			toReturn = Direction::South;
			break;

		case Direction::Uninitialized:
		default:
			assert(false);
			break;
		}

		return toReturn;
	}

	

	//data
	bool run = true;
	SearchType type;

	std::atomic_bool done = false;
	std::atomic_bool TopFoundEnd = true;
};

#endif

//--- End of File ------------------------------
