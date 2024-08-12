//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef POSITION_MAZE_H
#define POSITION_MAZE_H

#include "Direction.h"

class Position 
{
public:
	
	Position(int row, int col) 
	{
		this->row = row;
		this->col = col;
	}

	Position()
	{
		this->row = 0;
		this->col = 0;
	}

	bool operator ==( const Position &p ) const 
	{
		return ( (this->row == p.row) && (this->col == p.col));
	}

	Position move(Direction dir) 
	{
		Position tmp;

		switch(dir) 
		{
		case Direction::North:
			tmp = Position(row-1,col);
			break;

		case Direction::South:			
			tmp = Position(row+1,col);
			break;

		case Direction::East:
			tmp = Position(row,col+1);
			break;

		case Direction::West:
			tmp = Position(row,col-1);
			break;

		case Direction::Uninitialized:
		default:
			assert(false);
			break;
		}

		return tmp;
	}
		
	public: 
		// data
		int row;
		int col;
};

#endif

//--- End of File ------------------------------
