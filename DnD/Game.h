#pragma once

#include "Maze.h"

class CellDef;

class Game
{
public:
	Game();
	~Game();

	Maze::ptr getMaze() { return myMaze; }

protected:
	void initMaze();

	CellDef& getIndexCellDef(int index);

protected:
	Maze::ptr myMaze;
};

