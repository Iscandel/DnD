#include "Dragoon.h"

#include "Game.h"
#include "GameEngine.h"
#include "MessageBuilder.h"
#include "SGameServer.h"

Dragoon::Dragoon(int id, Game* game)
:GraphicEntity(id)
,myGame(game)
,myIsAwake(false)
{
}


Dragoon::~Dragoon()
{
}

void Dragoon::update(GameState& state, const Game& game, unsigned int)
{
	if (myGame->getCurrentIdTurn() != getId())
		return;

	//EntityStates could be used here (sleeping, chasing...))
	if (isAwake())
	{
		Player::ptr target = chooseTarget();
		if (target)
			moveToChoosenPlayer(state, target);
		else
			returnToTreasureRoom(state);
	}
}

bool Dragoon::onMoved(SGameServer& state)
{
	bool handled = false;
	std::vector<Player::ptr> players = myGame->getPlayers();

	for (Player::ptr player : players)
	{
		handled |= player->onArrivedOnCell(state, *this); //Choose best player if they are both on the same cell
	}

	return handled;
}

bool Dragoon::awakeIfSucceed(const Point<int>& pos)
{
	int sum = getDistanceTo(pos);
	//int sum = std::abs(pos.x - getAbstractX()) + std::abs(pos.y - getAbstractY());

	if (sum == 3)
	{
		int value = myRng.random(1, 100);
		if (value <= 50)
		{
			awake();
			return true;
		}
	}
	else if (sum == 2)
	{
		awake();
		return true;
	}

	return false;
}

Player::ptr Dragoon::chooseTarget()
{
	Player::ptr res;
	std::vector<Player::ptr> players = myGame->getPlayers();
	int minDist = 1e6;

	for (Player::ptr player : players)
	{
		if (player->hasTreasure())
			return player;

		int tmp = getDistanceTo(player->getAbstractPos());
		if (tmp < minDist && !player->isInSecretRoom())
		{
			res = player;
		}
	}

	return res;
}

int Dragoon::getDistanceTo(const Point<int> pos)
{
	return	std::abs(pos.x - getAbstractX()) + std::abs(pos.y - getAbstractY());
}

void Dragoon::moveToChoosenPlayer(GameState& state, Player::ptr player)
{
	int diffX = getAbstractX() - player->getAbstractX();
	int diffY = getAbstractY() - player->getAbstractY();
	
	Direction vert = diffY > 0 ? Direction::NORTH : diffY == 0 ?Direction::NONE : Direction::SOUTH;
	Direction horiz = diffX > 0 ? Direction::WEST : diffX == 0 ? Direction::NONE : Direction::EAST;

	Message msg = MessageBuilder::clDragoonMoves(vert, horiz);
	
	//state.getGameEngine()->processMessage(msg);
	state.sendMessage(msg, getId());
}

void Dragoon::returnToTreasureRoom(GameState& state)
{
	Treasure::ptr treasure = myGame->getTreasure();

	int diffX = getAbstractX() - treasure->getAbstractX();
	int diffY = getAbstractY() - treasure->getAbstractY();

	Direction vert = diffY > 0 ? Direction::NORTH : diffY == 0 ? Direction::NONE : Direction::SOUTH;
	Direction horiz = diffX > 0 ? Direction::WEST : diffX == 0 ? Direction::NONE : Direction::EAST;

	Message msg = MessageBuilder::clDragoonMoves(vert, horiz);

	//state.getGameEngine()->processMessage(msg);
	state.sendMessage(msg, getId());
}

//Dragoon receives player that just moved
bool Dragoon::onArrivedOnCell(SGameServer& state, Player& player)
{
	if (!isAwake())
	{
		if (awakeIfSucceed(player.getAbstractPos()))
		{
			Message msg = MessageBuilder::clDragonAwakes();
			state.processMessage(msg);
			return true;
		}
	}
	else
	{
		if (isReadyToAttack(player.getAbstractPos()))
		{
			attack(state, player);
			return true;
		}
	}

	return false;
}

bool Dragoon::onArrivedOnCell(SGameServer&, Dragoon&)
{
	return false;
}

bool Dragoon::isReadyToAttack(const Point<int>& pos)
{
	if (pos == getAbstractPos())
		return true;

	return false;
}

void Dragoon::attack(SGameServer& state, Player& target)
{
	if (target.hasTreasure())
	{
		Message msg = MessageBuilder::clPlayerLooses(target.getId());
		state.processMessage(msg);
	}
	else
	{
		Message msg = MessageBuilder::clPlayerWounded(target.getId());
		state.processMessage(msg);
	}
}
