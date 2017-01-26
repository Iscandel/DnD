#include "EmptyMazeGenerator.h"



EmptyMazeGenerator::EmptyMazeGenerator()
{
}


EmptyMazeGenerator::~EmptyMazeGenerator()
{
}

Maze::ptr EmptyMazeGenerator::generate(int x, int y)
{
	Maze::ptr maze = Maze::ptr(new Maze(x, y, true));

	for (int i = 1; i < maze->getSizeY() - 1; i++)
	{
		for (int j = 1; j < maze->getSizeX() - 1; j++)
		{
			auto factory = ObjectFactoryManager<Side>::getInstance()->getFactory("Void");
			maze->setSide(j, i, Direction::NORTH, factory->create());
			maze->setSide(j, i, Direction::EAST, factory->create());
			maze->setSide(j, i, Direction::WEST, factory->create());
			maze->setSide(j, i, Direction::SOUTH, factory->create());
		}
	}

	return maze;
}