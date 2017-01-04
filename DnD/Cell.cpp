#include "Cell.h"

Cell::Cell() {
	auto factory = ObjectFactoryManager<Side>::getInstance()->getFactory("Void");
	myEastSide = factory->create();
	myNorthSide = factory->create();
	myWestSide = factory->create();
	mySouthSide = factory->create();
}


Cell::Cell(Side::ptr east, Side::ptr north, Side::ptr west, Side::ptr south) {
	myEastSide = east;
	myNorthSide = north;
	myWestSide = west;
	mySouthSide = south;
}

Side::ptr Cell::getSide(Direction direction) {
	switch (direction) {
	case EAST:
		return myEastSide;
	case NORTH:
		return myNorthSide;
	case WEST:
		return myWestSide;
	case SOUTH:
		return mySouthSide;
	default:
		return nullptr;
	}
}

void Cell::setSide(Direction direction, Side::ptr side) {
	//		Side theSide = getSide(direction);
	//		if(theSide != null) {
	//			theSide = side;
	//		}
	switch (direction) {
	case EAST:
		myEastSide = side;
		break;
	case NORTH:
		myNorthSide = side;
		break;
	case WEST:
		myWestSide = side;
		break;
	case SOUTH:
		mySouthSide = side;
		break;
	default:
		break;
	}

}
