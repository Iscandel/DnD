#pragma once
#include "Maze.h"
class BaseMazeGenerator
{
public:
	BaseMazeGenerator();
	~BaseMazeGenerator();

	virtual Maze::ptr generate(int x, int y) = 0;
};

