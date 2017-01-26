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

	Player::ptr player = getWeakestPlayerOnDragoonCell();

	if(player)
		return player->onArrivedOnCell(state, *this);
	else
	{
		for (Player::ptr player : players)
		{
			bool res = player->onArrivedOnCell(state, *this); //Choose best player if they are both on the same cell
			if (res)
			{
				player->resetStepsRemaining();
				//while (player->hasStepsRemaining())
				//	player->doStep();
			}
			handled |= res;
		}
	}

	return handled;
}

Player::ptr Dragoon::getWeakestPlayerOnDragoonCell()
{
	bool handled = false;
	std::vector<Player::ptr> players = myGame->getPlayers();

	int minStrength = 1e6;

	Player::ptr res;

	std::vector<Player::ptr> candidates;

	for (Player::ptr player : players)
	{
		if (player->getAbstractPos() == getAbstractPos())
		{
			candidates.push_back(player);
		}
	}

	if (candidates.size() == 0)
		return res;

	res = candidates[0];
	minStrength = res->getStrength();
	

	for (unsigned int i = 1; i <  candidates.size(); i++)
	{
		if (candidates[i]->getStrength() < minStrength)
		{
			minStrength = candidates[i]->getStrength();
			res = candidates[i];
		}
	}

	return res;
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
	double minDist = 1e6;

	for (Player::ptr player : players)
	{
		if (player->hasTreasure())
			return player;

		double tmp = getEuclideanDistanceTo(player->getAbstractPos());
		if (tmp < minDist && !player->isInSecretRoom())
		{
			minDist = tmp;
			res = player;
		}
	}

	return res;
}

int Dragoon::getDistanceTo(const Point<int>& pos)
{
	return	std::abs(pos.x - getAbstractX()) + std::abs(pos.y - getAbstractY());
}

double Dragoon::getEuclideanDistanceTo(const Point<int>& pos)
{
	return	std::sqrt(std::pow(pos.x - getAbstractX(), 2) + std::pow(pos.y - getAbstractY(), 2));
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
		Game& game = state.getGameEngine()->getGame();
		Treasure::ptr treasure = game.getTreasure();
		treasure->setTaken(false);
		Message msg = MessageBuilder::clPlayerLooses(target.getId());
		state.processMessage(msg);
	}
	else
	{
		Message msg = MessageBuilder::clPlayerWounded(target.getId());
		state.processMessage(msg);
	}
}
