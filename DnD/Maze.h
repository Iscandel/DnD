#pragma once

#include "tools/Array2D.h"
#include "tools/WithSmartPtr.h"
#include "Direction.h"
#include "Side.h"
#include "Cell.h"

class Maze : public WithSmartPtr<Maze>
{
public:
	/**
	* Default constructor. Creates an empty maze, with wall on the edges.
	*/
	Maze();

	/**
	* constructor. Creates empty maze, with wall on the edges.
	*
	* @param nx : Size in the x dimension
	* @param ny : Size in the y dimension
	*/
	Maze(int nx, int ny);

	/**
	*
	* @param nx : Size in the x dimension
	* @param ny : Size in the y dimension
	* @param fullWalls : Maze with only walls on its sides and edges
	*/
	Maze(int nx, int ny, bool fullWalls);

	/**
	* Set a new side in the chosen direction of the chosen cell.
	*
	* @param x: x coordinate of the cell
	* @param y: y coordinate of the cell
	* @param direction: side direction
	* @param side: Type of side to set
	*/
	void setSide(int x, int y, Direction direction, Side::ptr side);

	/**
	* Returns the neighbour cell if it exists, null in the other case.
	*
	* @param x
	* @param y
	* @param direction
	* @return
	*/
	Cell::ptr getNeighbourCell(int x, int y, Direction direction);

	Cell::ptr getNeighbourCell(Cell::ptr cell, Direction direction);

	/**
	*  Indicates whether the cell is a valid cell regarding to the maze.
	* @param x
	* @param y
	* @return
	*/
	bool isValidCell(int x, int y);

	/**
	*
	* @return the size in the x dimension
	*/
	int getSizeX();

	/**
	*
	* @return the size in the y dimension
	*/
	int getSizeY();

	/**
	*
	* @param x
	* @param y
	* @return
	*/
	Cell::ptr getCell(int x, int y);

	/**
	*
	* @param x
	* @param y
	* @param c
	*/
	void setCell(int x, int y, Cell::ptr c);
	
protected:
	Array2D<Cell::ptr> myArray;
};

