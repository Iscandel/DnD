#include "Maze.h"

#include "MazeUtils.h"
#include "ObjectFactoryManager.h"

Maze::Maze()
{
	Maze(10, 10, false);
}

/**
* constructor. Creates empty maze, with wall on the edges.
*
* @param nx : Size in the x dimension
* @param ny : Size in the y dimension
*/
Maze::Maze(int nx, int ny)
{
	Maze(nx, ny, false);
}

/**
*
* @param nx : Size in the x dimension
* @param ny : Size in the y dimension
* @param fullWalls : Maze with only walls on its sides and edges
*/
Maze::Maze(int nx, int ny, bool fullWalls)
:myArray(nx, ny)
{
	//Walls needed because the completeMazeGenerator breaks walls
	auto wallFactory = ObjectFactoryManager<Side>::getInstance()->getFactory("Wall");

	//Fill with walls
	if (fullWalls)
	{
		for (int i = 0; i < ny; i++)
		{
			for (int j = 0; j < nx; j++)
			{
				setCell(j, i, Cell::ptr(new Cell(Point<int>(j, i), 
					wallFactory->create(), 
					wallFactory->create(), 
					wallFactory->create(), 
					wallFactory->create())));
			}
		}
	}


	//Link cells aside
	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < nx; j++)
		{
			Cell::ptr cell = getCell(j, i);

			if (i == 0)
			{
				cell->setSide(Direction::NORTH, wallFactory->create());
			}

			if (i == ny - 1)
			{
				cell->setSide(Direction::SOUTH, wallFactory->create());
			}
			else
			{
				cell->setSide(Direction::SOUTH, getCell(j, i + 1)->getSide(Direction::NORTH));
			}

			if (j == 0)
			{
				cell->setSide(Direction::WEST, wallFactory->create());
			}

			if (j == nx - 1)
			{
				cell->setSide(Direction::EAST, wallFactory->create());
			}
			else
			{
				cell->setSide(Direction::EAST, getCell(j + 1, i)->getSide(Direction::WEST));
			}
		}
	}
}

/**
* Set a new side in the chosen direction of the chosen cell.
*
* @param x: x coordinate of the cell
* @param y: y coordinate of the cell
* @param direction: side direction
* @param side: Type of side to set
*/
void Maze::setSide(int x, int y, Direction direction, Side::ptr side)
{
	Cell::ptr cell = getCell(x, y);
	cell->setSide(direction, side);

	Cell::ptr neighbour = getNeighbourCell(x, y, direction);
	if (neighbour != nullptr)
	{
		neighbour->setSide(MazeUtils::getOppositeDirection(direction), side);
	}
}

/**
* Returns the neighbour cell if it exists, null in the other case.
*
* @param x
* @param y
* @param direction
* @return
*/
Cell::ptr Maze::getNeighbourCell(int x, int y, Direction direction)
{
	int newX = x;
	int newY = y;

	switch (direction)
	{
	case EAST:
		newX = x + 1;
		break;

	case WEST:
		newX = x - 1;
		break;

	case SOUTH:
		newY = y + 1;
		break;

	case NORTH:
		newY = y - 1;
		break;
	default:
		break;
	}

	if (isValidCell(newX, newY))
		return getCell(newX, newY);
	return nullptr;
}

Cell::ptr Maze::getNeighbourCell(Cell::ptr cell, Direction direction)
{
	int i = 0;
	int j = 0;
	bool found = false;

	for (i = 0; i < getSizeY() && !found; i++)
	{
		for (j = 0; j < getSizeX(); j++)
		{
			if (cell == getCell(j, i))
			{
				found = true;
				break;
			}

		}
	}

	i--;
	return getNeighbourCell(j, i, direction);
}

/**
*  Indicates whether the cell is a valid cell regarding to the maze.
* @param x
* @param y
* @return
*/
bool Maze::isValidCell(int x, int y) const
{
	return (x >= 0 && x < getSizeX() && y >= 0 && y < getSizeY());
}

/**
*
* @return the size in the x dimension
*/
int Maze::getSizeX() const 
{
	return myArray.getWidth();
}

/**
*
* @return the size in the y dimension
*/
int Maze::getSizeY() const
{
	return myArray.getHeight();
}

/**
*
* @param x
* @param y
* @return
*/
Cell::ptr Maze::getCell(int x, int y)
{
	return myArray(x, y);
}

/**
*
* @param x
* @param y
* @param c
*/
void Maze::setCell(int x, int y, Cell::ptr c)
{
	myArray(x, y) = c;
}

std::ostream& operator <<(std::ostream& os, Maze& maze)
{
	for (int i = 0; i < maze.getSizeY(); i++)
	{
		//Top walls
		if (i == 0)
		{
			for (int j = 0; j < maze.getSizeX() * 2 + 1; j++)
				os << "#";
			os << std::endl;
		}

		for (int j = 0; j < maze.getSizeX(); j++)
		{
			//left wall
			if (j == 0)
				os << "#";

			os << ".";

			Cell::ptr cell = maze.getCell(j, i);
			os << *cell->getSide(Direction::EAST);
		}

		//Next line
		os << std::endl;

		//Iterate again for bottom walls...
		for (int j = 0; j < maze.getSizeX(); j++)
		{
			//left wall
			if (j == 0)
				os << "#";

			Cell::ptr cell = maze.getCell(j, i);
			os << *cell->getSide(Direction::SOUTH);

			os << "#";
		}

		os << std::endl;
	}
	
	return os;
}