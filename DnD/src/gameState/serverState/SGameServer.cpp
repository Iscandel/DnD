#include "SGameServer.h"

#include "maze/CompleteMazeGenerator.h"
#include "game/Direction.h"
#include "game/GameEngine.h"
#include "game/MessageBuilder.h"
#include "network/NetworkEngine.h"

SGameServer::SGameServer()
{
}


SGameServer::~SGameServer()
{
}

void SGameServer::init()
{
	//Initialize maze
	Game& game = getGameEngine()->getGame();

	CompleteMazeGenerator gene(game.getMazeUnperfectPerc());

	game.createMaze(gene, game.getMazeSize(), game.getMazeSize());

	Message msg = MessageBuilder::svGameRunning();
	sendMessage(msg);
}

bool SGameServer::catchEvent(const sf::Event&)
{
	return false;
}

void SGameServer::update()
{
	processQueue();

	//Game& game = getGameEngine()->getGame();
	//game.update(getGraphicEngine()->getElapsedTime());

	//std::vector<TimerFunction>::iterator it = myTimerFunctions.begin();
	//for (; it != myTimerFunctions.end();)
	//{

	//	it->update(getGraphicEngine()->getElapsedTime());
	//	if (it->isFinished())
	//		it = myTimerFunctions.erase(it);
	//	else
	//		++it;
	//}

	//for(int i = 0; i < game.getNumberPlayers(); i++)
	//{
	//	PtrPlayer player = game.getPlayerByPosition(i);
	//	player->update(game, getGraphicEngine()->getElapsedTime());
	//}

	//game.getTable().update(getGraphicEngine()->getElapsedTime());
}

void SGameServer::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::CL_MOVE:
	{
		//msg.iData[Message::Key::clMove::ID] = 1; //to change

		Direction direction;
		int id;
		if (!MessageBuilder::extractClMove(msg, direction, id))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);

		if (!player || id != game.getCurrentIdTurn())
			return;

		//Should not happen
		if (nextPlayerIfHasLost(player))
			return;

		Maze::ptr maze = game.getMaze();
		Cell::ptr cell = maze->getCell(player->getAbstractX(), player->getAbstractY());

		//Renew player strength
		player->tryRenewStrength();
		
		if (cell && cell->getSide(direction)->getType() != Side::WALL)
		{
			Cell::ptr neighbour = maze->getNeighbourCell(cell, direction);
			if (neighbour)
			{
				const Point<int>& coords = neighbour->getAbstractPos();
				player->setAbstractPosition(coords.x, coords.y);
				Message m = MessageBuilder::svPlayerMove(id, coords);
				//getGameEngine()->processMessage(m);

				sendMessage(m);

				player->doStep();
				if (!player->onMoved(*this)) //on moved should return true if next turn has to be called ?
				{
					if (!player->hasStepsRemaining()) {
						player->resetStepsRemaining();
						int nextId = game.nextEntityTurn();
						if (nextId == -1)
							return;
						Message m = MessageBuilder::svNewTurn(nextId);
						//getGameEngine()->processMessage(m);
						sendMessage(m);
					}
				}
				else
				{
					Message m = MessageBuilder::svGameWon(player->getId()); //Should be called elsewhere ?
					//getGameEngine()->processMessage(m);

					sendMessage(m);

					std::cout << "Jeu gagn�" << std::endl;
				}
			}
		}
		else if (cell && cell->getSide(direction)->getType() == Side::WALL)
		{
			cell->getSide(direction)->revealSide(); //to change
			player->resetStepsRemaining();
			std::cout << "On envoie " << cell->getAbstractX() << " " << cell->getAbstractY() << std::endl;
			Message m = MessageBuilder::svWall(cell->getAbstractX(), cell->getAbstractY(), direction);
			sendMessage(m);
			
			//next turn
			int nextId = game.nextEntityTurn();
			m = MessageBuilder::svNewTurn(nextId);
			sendMessage(m);
			//getGameEngine()->processMessage(m);
		}
	}
	break;

	case Message::MessageType::CL_DRAGOON_AWAKES:
	{
		Message m = MessageBuilder::svDragonAwakes();
		sendMessage(m);
	}
	break;

	case Message::MessageType::CL_PLAYER_LOOSES: //make a message network filter
	{
		int id;
		if (!MessageBuilder::extractClPlayerLooses(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);

		handlePlayerDefeat(player);
	}
	break;

	case Message::MessageType::CL_PLAYER_WOUNDED:
	{
		int id;
		if (!MessageBuilder::extractClPlayerWounded(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);

		while (player->hasStepsRemaining())
			player->doStep();

		if (player->hasMoreThanOneLife())
		{
			player->setAbstractPosition(player->getSecretRoomPos());
			player->removeOneLife();
			Message m = MessageBuilder::svPlayerWounded(id, player->getNumberOfLives());

			sendMessage(m);

			////Only players can play after a dragoon attack
			//int nextId = game.nextPlayerTurn();
			//m = MessageBuilder::svNewTurn(nextId);
			////getGameEngine()->processMessage(m);
			//sendMessage(m);
		}
		else
		{
			handlePlayerDefeat(player);

			//checkGameOver();
		}
	}
	break;

	case Message::MessageType::CL_END_TURN:
	{
		Game& game = getGameEngine()->getGame();

		int id;
		if (!MessageBuilder::extractClEndTurn(msg, id))
			return;

		if (id != game.getCurrentIdTurn())
			return;

		//Should not happen
		Player::ptr player = game.getPlayer(id);
		if (nextPlayerIfHasLost(player))
			return;

		player->resetStepsRemaining();
		
		int nextId = game.nextEntityTurn();
		Message m = MessageBuilder::svNewTurn(nextId);
		//getGameEngine()->processMessage(m);
		sendMessage(m);
	}
	break;

	case Message::MessageType::CL_DRAGOON_MOVES: //filter
	{
		Direction dirHoriz, dirVert;
		int id;
		if (!MessageBuilder::extractClDragoonMoves(msg, dirVert, dirHoriz, id))
			return;

		Game& game = getGameEngine()->getGame();
		Dragoon::ptr dragoon = game.getDragoon();

		Maze::ptr maze = game.getMaze();
		Cell::ptr cell = maze->getCell(dragoon->getAbstractX(), dragoon->getAbstractY());
		
		Cell::ptr neighbour = cell;

		if (dirVert != Direction::NONE)
		{
			neighbour = maze->getNeighbourCell(cell, dirVert);
			if(dirHoriz != Direction::NONE)
				neighbour = maze->getNeighbourCell(neighbour, dirHoriz);

		
		}
		else if (dirHoriz != Direction::NONE)
		{
			neighbour = maze->getNeighbourCell(cell, dirHoriz);
			if (dirVert != Direction::NONE)
				neighbour = maze->getNeighbourCell(neighbour, dirVert);
		}

		if (neighbour != cell)
		{
			const Point<int>& coords = neighbour->getAbstractPos();
			dragoon->setAbstractPosition(coords.x, coords.y);
			Message m = MessageBuilder::svDragoonMoves();
			sendMessage(m);

			//Dragoon has attacked
			if (dragoon->onMoved(*this))
			{
				//Only players can play after a dragoon attack
				int nextId = game.nextPlayerTurn();
				if (nextId == -1)
					return;
				m = MessageBuilder::svNewTurn(nextId);
				//getGameEngine()->processMessage(m);
				sendMessage(m);
			}
			else //Dragoon has only moved
			{
				int nextId = game.nextEntityTurn();
				Message m = MessageBuilder::svNewTurn(nextId);
				sendMessage(m);
			}
		}
		else //Dragoon has not moved (stays in treasure room)
		{
			int nextId = game.nextEntityTurn();
			Message m = MessageBuilder::svNewTurn(nextId);
			sendMessage(m);
		}
	}
	break;

	case Message::MessageType::CL_SEND_CHAT_MESSAGE:
	{
		int id;
		std::string strMessage;
		if (!MessageBuilder::extractClSendChatMessage(msg, id, strMessage))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);

		if (player)
		{
			std::string toSend = "[" + player->getName() + "] says: " + strMessage;

			Message m = MessageBuilder::svSendChatMessage(toSend);
			sendMessage(m);
		}
	}
	break;
	
	default:
		break;
	}
}

void SGameServer::handlePlayerDefeat(Player::ptr player)
{
	player->defeat();

	Game& game = getGameEngine()->getGame();
	game.getManager().removeEntity(player->getId());

	Message m = MessageBuilder::svPlayerLooses(player->getId());
	sendMessage(m);

	checkGameOver();
}

void SGameServer::checkGameOver()
{
	bool gameOver = true;
	Game& game = getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();

	for (Player::ptr player : players)
	{
		if (!player->hasLost())
			gameOver = false;
	}

	if (gameOver)
	{
		Message msg = MessageBuilder::svGameOver();
		sendMessage(msg);
		getGameEngine()->popServerState();
	}
}

bool SGameServer::nextPlayerIfHasLost(Player::ptr player)
{
	if (player->hasLost())
	{
		Game& game = getGameEngine()->getGame();
		int nextId = game.nextEntityTurn();
		Message m = MessageBuilder::svNewTurn(nextId);
		sendMessage(m);
		return true;
	}

	return false;
}

//void SGameServer::sendMessage(const Message& msg)
//{
//	getGameEngine()->processMessage(msg);
////	getNetworkEngine()->sendMessageTCPToAll(msg);
//}
//
//void SGameServer::sendMessage(const Message& msg, int id)
//{
////	getNetworkEngine()->sendMessageTCPToAllExcept(msg, id);
//}
//
//void SGameServer::sendMessageExceptLocal(const Message& msg)
//{
////	getNetworkEngine()->sendMessageTCPToAll(msg);
//}
//
//void SGameServer::sendMessageToAllExceptSome(const Message& msg, const std::vector<int>& excluded)
//{
//	Game& game = getGameEngine()->getGame();
//	bool notLocal = false;
//
//	for (int excl : excluded)
//	{
////		if (game.isLocalId(excl))
//			notLocal = true;
//	}
//
//	if (!notLocal)
//		getGameEngine()->processMessage(msg);
//
////	getNetworkEngine()->sendMessageTCPToAllExcept(msg, excluded)
//}