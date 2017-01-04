#pragma once
#include "BaseMazeGenerator.h"
#include "Maze.h"

class CompleteMazeGenerator :
	public BaseMazeGenerator
{
public:
	class CellCoords
	{
	public:
		int x;
		int y;
		Cell::ptr myCell;

		CellCoords() {}

		CellCoords(int x, int y, Cell::ptr cell)
		{
			this->x = x;
			this->y = y;
			myCell = cell;
		}

		bool operator == (const CellCoords& other)
		{
			if (this == &other)
				return true;
			if (x == other.x && y == other.y && myCell == other.myCell)
				return true;

			return false;
		}
	};

public:
	CompleteMazeGenerator(int percUnperfect);
	~CompleteMazeGenerator();

	Maze::ptr generate(int x, int y) override;

	void generatePerfect(Maze::ptr maze);
	void generateUnperfect(Maze::ptr maze, int perc);
	void breakWall(Maze::ptr maze, const CellCoords& first, Direction direction);

protected:
	int myPercentage;
};
