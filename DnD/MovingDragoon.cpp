#include "MovingDragoon.h"

#include "Game.h"
#include "Dragoon.h"

MovingDragoon::MovingDragoon()
{
}


MovingDragoon::~MovingDragoon()
{
}

void MovingDragoon::init(Dragoon& parent)
{

}

void MovingDragoon::free(Dragoon& parent)
{

}

void MovingDragoon::update(Dragoon& parent, GameState& state, const Game& game, unsigned int elapsedTime)
{
	if (game.getCurrentIdTurn() != parent.getId())
		return;

	//EntityStates could be used here (sleeping, chasing...))
	if (parent.isAwake())
	{
		Player::ptr target = parent.chooseTarget();
		if (target)
			parent.moveToChoosenPlayer(state, target);
		else
			parent.returnToTreasureRoom(state);
	}
}