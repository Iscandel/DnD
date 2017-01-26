#include "Player.h"

#include "Dragoon.h"
#include "Game.h"
#include "GameEngine.h"
#include "MessageBuilder.h"
#include "SGameServer.h"
#include "Treasure.h"

Player::Player(int id, Game* game)
:GraphicEntity(id)
,myGame(game)
,myLives(LIVE_3)
,myHasTreasure(false)
,myHasLost(false)
,STEPS_TREASURE(4)
{
	myStepsByLives[LIVE_1] = STEPS_1;
	myStepsByLives[LIVE_2] = STEPS_2;
	myStepsByLives[LIVE_3] = STEPS_3;

	myCurrentMaxSteps = myStepsByLives[myLives];
	resetStepsRemaining();
}


Player::~Player()
{
}

void Player::update(GameState& state, const Game& game, unsigned int elapsedTime)
{

}

int Player::getMaxSteps() const
{
	if (hasTreasure())
		return STEPS_TREASURE;

	return myCurrentMaxSteps;
	//if (myLives == 3) {
	//	return LIVE_3;
	//}
	//else if (myLives == 2) {
	//	return LIVE_2;
	//}
	//else if (myLives == 1) {
	//	return LIVE_1;
	//}
	//else
	//	throw std::runtime_error("Number of lives not correct.\n");
}


void Player::removeOneLife()
{
	if (myLives == LIVE_1)
	{
		throw std::runtime_error("Life removed whereas only one left.\n");
	}

	myLives = (Lives)(myLives - 1);
	myCurrentMaxSteps = myStepsByLives[myLives];
}

bool Player::onMoved(SGameServer& state)
{
	if (hasTreasure() && getAbstractPos() == getSecretRoomPos())
	{
		return true;
	}

	Dragoon::ptr dragoon = myGame->getDragoon();

	dragoon->onArrivedOnCell(state, *this);

	std::vector<Player::ptr> players = myGame->getPlayers();

	for (Player::ptr player : players)
	{
		if (player.get() != this)
			player->onArrivedOnCell(state, *this);
	}

	Treasure::ptr treasure = myGame->getTreasure();

	treasure->onArrivedOnCell(state, *this);

	return false;
}


//Player receives player moving
bool Player::onArrivedOnCell(SGameServer& state, Player& player)
{
	if (hasTreasure() || player.hasTreasure())
	{
//		fightForTreasure(player);
	}

	return true;
}

//Player receives dragoon
bool Player::onArrivedOnCell(SGameServer& state, Dragoon& dragoon)
{
	//of course, should never happen. If dragoon is a 
	//parameter, it means it moves
	if (!dragoon.isAwake())
	{
		if (dragoon.awakeIfSucceed(getAbstractPos()))
		{
			Message msg = MessageBuilder::clDragonAwakes();
			state.processMessage(msg);
			return false;//true;
		}
	}
	else
	{
		if (dragoon.isReadyToAttack(getAbstractPos()))
		{
			dragoon.attack(state, *this);
			return true;
		}
	}

	return false;
}

