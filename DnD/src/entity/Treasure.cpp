#include "Treasure.h"

#include "Dragoon.h"
#include "game/Game.h"
#include "game/MessageBuilder.h"
#include "Player.h"
#include "gameState/serverState/SGameServer.h"


Treasure::Treasure(int id, Game* game)
:GraphicEntity(id)
,myGame(game)
,myIsTaken(false)
{
}


Treasure::~Treasure()
{
}

bool Treasure::onArrivedOnCell(SGameServer& state, Player& player)
{
	if (!wasTaken())
	{
		if (getAbstractX() == player.getAbstractX() && getAbstractY() == player.getAbstractY())
		{
			takeTreasure(state, player);
			Message msg = MessageBuilder::svTakeTreasure(player.getId());
			state.sendMessage(msg);
			
			msg = MessageBuilder::clEndTurn(player.getId());
			state.sendMessage(msg);

			return true;
		}
	}

	return false;
}

bool Treasure::onArrivedOnCell(SGameServer&, Dragoon&)
{
	return false;
}

void Treasure::takeTreasure(SGameServer& state, Player& player)
{
	setTaken(true);

	std::vector<Player::ptr> players = myGame->getPlayers();

	for (Player::ptr tmpPlayer : players)
	{
		tmpPlayer->setTreasure(false);
	}

	player.setTreasure(true);
}
