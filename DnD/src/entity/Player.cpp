#include "Player.h"

#include "Dragoon.h"
#include "game/Game.h"
#include "game/GameEngine.h"
#include "game/MessageBuilder.h"
#include "gameState/serverState/SGameServer.h"
#include "Treasure.h"

Player::Player(int id, Game* game)
:GraphicEntity(id)
,myGame(game)
,myLives(LIVE_3)
,myHasTreasure(false)
,MAX_STRENGTH(20)
,STEPS_TREASURE(4)
,RENEW_STRENGTH_FREQ(20)
{
	myStepsByLives[LIVE_1] = STEPS_1;
	myStepsByLives[LIVE_2] = STEPS_2;
	myStepsByLives[LIVE_3] = STEPS_3;

	myStrength = MAX_STRENGTH;

	myCurrentMaxSteps = myStepsByLives[myLives];
	resetStepsRemaining();

	myAbstractPos = Point<int>(-1, -1);
	//mySecretRoom = Point<int>(-1, -1);
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

void Player::setTreasure(bool treasure)
{
	if (treasure && getCurrentStepsRemaining() > STEPS_TREASURE)
		setCurrentStepsRemaining(STEPS_TREASURE);
	
	myHasTreasure = treasure;
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
	if ((hasTreasure() || player.hasTreasure()) && player.getAbstractPos() == getAbstractPos())
	{
		fightForTreasure(state, player);
		return true;
	}

	return false;
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
		if (dragoon.isReadyToAttack(getAbstractPos())) //maybe a test if dragoon and other player already occupy the cell ?
		{
			dragoon.attack(state, *this);
			return true;
		}
	}

	return false;
}

void Player::fightForTreasure(SGameServer& state, Player& player)
{
	std::vector<Player::ptr> players = myGame->getPlayers();

	std::cout << "player receiving has " << getStrength() << " vs " << player.getStrength() << std::endl;

	for (Player::ptr tmpPlayer : players)
	{
		tmpPlayer->setTreasure(false);
	}

	if (getStrength() > player.getStrength())
	{
		setTreasure(true);
	}
	else if (getStrength() < player.getStrength())
	{
		player.setTreasure(true);
	}
	else
	{
		if(myRandom.random(1, 2) == 1)
			setTreasure(true);
		else
			player.setTreasure(true);
	}

	Message msg = MessageBuilder::svPlayerTakesTreasureFromPlayer((hasTreasure() ? getId() : player.getId()));
	state.sendMessage(msg);

	std::cout << "winner is " << (hasTreasure() ? getId() : player.getId()) << std::endl;
}

void Player::tryRenewStrength()
{
	int value = myRandom.random(1, 100);
	if (value <= RENEW_STRENGTH_FREQ)
	{
		myStrength = MAX_STRENGTH;
	}
}

