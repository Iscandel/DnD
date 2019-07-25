#pragma once
#include "BaseMazeGenerator.h"

class EmptyMazeGenerator :
	public BaseMazeGenerator
{
public:
	EmptyMazeGenerator();
	~EmptyMazeGenerator();

	Maze::ptr generate(int x, int y) override;
};

