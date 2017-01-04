#pragma once

#include "Side.h"
#include "Direction.h"

#include "ObjectFactoryManager.h"
#include "tools/WithSmartPtr.h"

class Cell : public WithSmartPtr<Cell>
{
public:
	/**
	* Constructor without arguments.
	* All sides are set to Void.
	*/
	Cell();

	/**
	* Constructor with arguments.
	* @param east
	* @param north
	* @param west
	* @param south
	*/
	Cell(Side::ptr east, Side::ptr north, Side::ptr west, Side::ptr south);

	/**
	*
	* @param direction
	* @return the corresponding side
	*/
	Side::ptr getSide(Direction direction);

	void setSide(Direction direction, Side::ptr side);

protected:
	//public boolean visitee = false;
	/**
	* The east side.
	*/
	Side::ptr myEastSide;

	/**
	* The north side.
	*/
	Side::ptr myNorthSide;

	/**
	* The west side.
	*/
	Side::ptr myWestSide;

	/**
	* The south side.
	*/
	Side::ptr mySouthSide;


};

