#include "SGameBeginningServer.h"

#include "maze/CompleteMazeGenerator.h"
#include "game/Game.h"
#include "gameState/clientState/SGameBeginning.h"
#include "game/GameEngine.h"
#include "game/GameUtils.h"
#include "graphic/GraphicEngine.h"
#include "game/MessageBuilder.h"
#include "SGameServer.h"
#include "tools/Logger.h"

SGameBeginningServer::SGameBeginningServer()
{
}


SGameBeginningServer::~SGameBeginningServer()
{
}

void SGameBeginningServer::init()
{
	//Initialize maze
	//Game& game = getGameEngine()->getGame();

	getGameEngine()->setClientGameState(GameState::ptr(new SGameBeginning));

	Message msg = MessageBuilder::svNextState();
	sendMessageExceptLocal(msg);

	//CompleteMazeGenerator gene(game.getMazeUnperfectPerc());

	//game.createMaze(gene, game.getMazeSize(), game.getMazeSize());
}

bool SGameBeginningServer::catchEvent(const sf::Event&)
{
	return false;
}

void SGameBeginningServer::update()
{
	processQueue();

	//std::vector<TimerFunction>::iterator it = myTimerFunctions.begin();
	//for (; it != myTimerFunctions.end();)
	//{

	//	it->update(getGraphicEngine()->getElapsedTime());
	//	if (it->isFinished())
	//		it = myTimerFunctions.erase(it);
	//	else
	//		++it;
	//}
}

void SGameBeginningServer::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::CL_CHOOSES_SECRET_ROOM:
	{
		int id, x, y;
		if (!MessageBuilder::extractClChoosesSecretRoom(msg, id, x, y))
			return;

		Game& game = getGameEngine()->getGame();

		if (id != game.getCurrentIdTurn())
			return;

		if (isOnSamePos(id, x, y))
			return;

		Player::ptr player = game.getPlayer(id);
		if (player)
		{
			if (isValid(x, y))
			{
				myChosenRoomById[id] = Point<int>(x, y);
				player->setSecretRoomPos(Point<int>(x, y));
				player->setAbstractPosition(player->getSecretRoomPos());

				Message m = MessageBuilder::svSecretRoomChosen(id, x, y);
				sendMessageExceptLocal(m);

				if (allSecretRoomValidated())
				{
					configureMaze();
					game.setTurnToFirstPlayer();

					int nextId = game.getCurrentIdTurn();
					Message m = MessageBuilder::svNewTurn(nextId);
					sendMessageExceptLocal(m);

					//m = MessageBuilder::svNextState();
					//sendMessageExceptLocal(m);

					setServerGameState(GameState::ptr(new SGameServer));
				}
				else
				{
					int nextId = game.nextPlayerTurn();
					Message m = MessageBuilder::svNewTurn(nextId);
					sendMessage(m);
				}
			}
		}
		else //Should not happen
		{
			ILogger::log() << "Choosing room. Player " << id << " should exist.\n";
			int nextId = game.nextPlayerTurn();
			Message m = MessageBuilder::svNewTurn(nextId);
			sendMessage(m);
		}
	}
	break;

	default:
		break;
	}
}

bool SGameBeginningServer::isValid(int x, int y)
{
	const Game& game = getGameEngine()->getGame();
	return (x >= 0 && x < game.getMazeSize() && y >= 0 && y < game.getMazeSize());
}

bool SGameBeginningServer::isOnSamePos(int id, int x, int y) const
{
	std::map<int, Point<int>>::const_iterator it = myChosenRoomById.cbegin();
	for (it; it != myChosenRoomById.cend(); ++it)
	{
		if (it->first == id)
			return true;

		if (it->second.x == x && it->second.y == y)
			return true;
	}

	return false;
}

bool SGameBeginningServer::allSecretRoomValidated()
{
	Game& game = getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();

	for (Player::ptr player : players)
	{
		if (myChosenRoomById.find(player->getId()) == myChosenRoomById.end())
			return false;
	}

	return true;
}

void SGameBeginningServer::configureMaze()
{
	Game& game = getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();

	CompleteMazeGenerator gene(game.getMazeUnperfectPerc());
	Maze::ptr maze = game.createMaze(gene, game.getMazeSize(), game.getMazeSize());

	std::vector<Point<int>> cells;
	
	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			cells.push_back(Point<int>(j, i));
		}
	}

	bool validated = false;
	while (!validated)
	{
		validated = true;
		int index = myRng.random(0, cells.size() - 1);
		const Point<int>& cell = cells[index];
		std::vector<Player::ptr> players = game.getPlayers();

		for (Player::ptr player : players)
		{
			if (GameUtils::getDistanceTo(cell, player->getSecretRoomPos()) < 3)
			{
				validated = false;
			}
		}

		if (validated)
		{
			Dragoon::ptr dragoon = game.getDragoon();
			dragoon->setAbstractPosition(cell);

			Treasure::ptr treasure = game.getTreasure();
			treasure->setAbstractPosition(cell);
		}
		else
		{
			cells.erase(cells.begin() + index);
		}
	}
}