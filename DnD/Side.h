#pragma once

#include "tools/WithSmartPtr.h"
#include "Action.h"

#include <iostream>

class Side : public WithSmartPtr<Side>
{
public:
	enum SideType {
		VOID,
		WALL,
		DOOR
	};

public:
	Side();
	~Side();

	///sets revealed status to True.
	void revealSide() { myIsRevealed = true;}

	void setAction(Action::ptr action) { myAction = action; }

	//void onPassTrough(Player::ptr player) { myAction.action(player); }	
	
	///returns side's status
	bool isRevealed() {return myIsRevealed;}
	
	void setType(SideType type) { myType = type; }

	SideType getType() const { return myType; }

	friend std::ostream& operator <<(std::ostream& os, const Side& maze)
	{
		if (maze.getType() == WALL)
			os << "#";
		else if (maze.getType() == VOID)
			os << ".";
		else
			os << "\"";

		return os;
	}
private:
	///Side's status
	bool myIsRevealed;

	Action::ptr myAction;

	SideType myType;
};

