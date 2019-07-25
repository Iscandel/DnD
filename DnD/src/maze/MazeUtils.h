#pragma once
#include "game/Direction.h"

class MazeUtils {
public:
	static Direction getOppositeDirection(Direction direction)
	{
		if (direction == Direction::EAST)
			return Direction::WEST;
		if (direction == Direction::WEST)
			return Direction::EAST;
		if (direction == Direction::NORTH)
			return Direction::SOUTH;
		if (direction == Direction::SOUTH)
			return Direction::NORTH;

		return direction;
	}

	static Direction getDirection(int xFrom, int yFrom, int xTo, int yTo)
	{
		if (xFrom > xTo)
			return Direction::WEST;
		if (xFrom < xTo)
			return Direction::EAST;
		if (yFrom > yTo)
			return Direction::NORTH;
		if (yFrom < yTo)
			return Direction::SOUTH;

		return Direction::NONE;//Direction.END;
	}
};


