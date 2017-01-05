#include "CompleteMazeGenerator.h"

#include "MazeUtils.h"
#include "tools/Rng.h"

#include <stack>
#include <vector>

CompleteMazeGenerator::CompleteMazeGenerator(int percUnperfect)
:myPercentage(percUnperfect)
{
}


CompleteMazeGenerator::~CompleteMazeGenerator()
{
}

Maze::ptr CompleteMazeGenerator::generate(int x, int y)
{
	Maze::ptr maze = Maze::ptr(new Maze(x, y, true));

	//fillWithWalls(maze);

	generatePerfect(maze);

	generateUnperfect(maze, myPercentage);

	return maze;
}

void CompleteMazeGenerator::generatePerfect(Maze::ptr maze)
{
	CellCoords currentCell;
	std::stack<CellCoords> cellList;// = new Stack<CellCoords>();

	//Vector<bool> is a special specialization class that causes 
	//some compilation troubles here...so let's use int
	Array2D<int> visitedCells(maze->getSizeY(), maze->getSizeX());
	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			visitedCells(i, j) = 0;
		}
	}

	//boolean init = true;
	Rng rng;
	int randX = rng.random(0, maze->getSizeX() - 1);
	int randY = rng.random(0, maze->getSizeY() - 1);
	//Random random = new Random();
	//int randX = random.nextInt(maze.getSizeX());
	//int randY = random.nextInt(maze.getSizeY());

	currentCell = CellCoords(randX, randY, maze->getCell(randX, randY));
	//currentCell.myCell.visitee = true;
	visitedCells(randY, randX) = 1;

	cellList.push(currentCell);

	do//(init || currentCell.myCell != maze.getCell(randX, randY))
	{
		//init = false;
		std::vector<CellCoords> vec;// = new ArrayList<CellCoords>();

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int tmpX = currentCell.x + j;
				int tmpY = currentCell.y + i;

				//Check for valid cells around and ignore diagonal cells (+ the current one)
				if (std::abs(i) != std::abs(j) && maze->isValidCell(tmpX, tmpY) && !((bool)visitedCells(tmpY, tmpX)))
				{
					vec.push_back(CellCoords(tmpX, tmpY, maze->getCell(tmpX, tmpY)));
				}
			}
		}

		//try to chose next cell
		if (vec.size() != 0)
		{
			int vecInt = rng.random(0, vec.size() - 1);
			CellCoords chosenCell = vec[vecInt];
			visitedCells(chosenCell.y, chosenCell.x) = 1;
			//chosenCell.myCell.visitee = true;

			breakWall(maze, currentCell, MazeUtils::getDirection(currentCell.x,
				currentCell.y,
				chosenCell.x,
				chosenCell.y));
			//currentCell, chosenCell);

			currentCell = chosenCell;

			cellList.push(currentCell);
		}
		else
		{
			currentCell = cellList.top();
			cellList.pop();
		}

	} while (currentCell.myCell != maze->getCell(randX, randY));
}

void CompleteMazeGenerator::generateUnperfect(Maze::ptr maze, int perc)
{
	Rng rng;
	//Random random = new Random();

	std::vector<CellCoords> list;// = new ArrayList<CellCoords>();

	for (int i = 1; i < maze->getSizeY() - 1; i++)
	{
		for (int j = 1; j < maze->getSizeX() - 1; j++)
		{
			list.push_back(CellCoords(j, i, maze->getCell(j, i)));
		}
	}

	int nb = (int)((int)(list.size() * perc) / 100.f);
	for (int i = 0; i < nb; i++)
	{
		int randVal = rng.random(0, list.size() - 1);

		CellCoords cell = list[randVal];
		bool broken = false;
		Direction direction = Direction::EAST;
		while (!broken)
		{

			int randDir = rng.random(0, 4 - 1);//random.nextInt(4);


			if (randDir == 0)
			{
				direction = Direction::EAST;
			}
			else if (randDir == 1)
			{
				direction = Direction::NORTH;
			}
			else if (randDir == 2)
			{
				direction = Direction::WEST;
			}
			if (randDir == 3)
			{
				direction = Direction::SOUTH;
			}

			if (cell.myCell->getSide(direction)->getType() == Side::WALL)
			{
				auto factory = ObjectFactoryManager<Side>::getInstance()->getFactory("Void");
				maze->setSide(cell.x, cell.y, direction, factory->create());
				broken = true;
			}
		}

		if (!(cell.myCell->getSide(Direction::EAST)->getType() == Side::WALL ||
			cell.myCell->getSide(Direction::WEST)->getType() == Side::WALL ||
			cell.myCell->getSide(Direction::SOUTH)->getType() == Side::WALL ||
			cell.myCell->getSide(Direction::NORTH)->getType() == Side::WALL)
			)
		{
			list.erase(std::find(list.begin(), list.end(), cell));
		}

		Cell::ptr neighbour = maze->getNeighbourCell(cell.x, cell.y, direction);
		if (!(neighbour->getSide(Direction::EAST)->getType() == Side::WALL ||
			neighbour->getSide(Direction::WEST)->getType() == Side::WALL ||
			neighbour->getSide(Direction::SOUTH)->getType() == Side::WALL ||
			neighbour->getSide(Direction::NORTH)->getType() == Side::WALL)
			)
		{
			for (int k = 0; k < list.size(); k++)
			{
				if (list[k].myCell == neighbour)
				{
					list.erase(list.begin() + k);
					break;
				}
			}

		}
	}

	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{

		}
	}
}

void CompleteMazeGenerator::breakWall(Maze::ptr maze, const CellCoords& first, Direction direction)
{
	auto factory = ObjectFactoryManager<Side>::getInstance()->getFactory("Void");
	maze->setSide(first.x, first.y, direction, factory->create());
}