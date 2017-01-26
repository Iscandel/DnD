#include "SGame.h"

#include "GameEngine.h"
#include "GameView.h"
#include "GraphicEngine.h"
#include "MessageBuilder.h"
#include "NetworkEngine.h"
#include "SoundEngine.h"
#include "TextureManager.h"
#include "tools/Logger.h"
//#include "tools/Tools.h"

#include "CompleteMazeGenerator.h"

SGame::SGame(void)
{
	myTurnSoundByPlayerVectorPos.push_back("p1NewTurn");
	myTurnSoundByPlayerVectorPos.push_back("p2NewTurn");
}


SGame::~SGame(void)
{
}

void SGame::init()
{
	setView(View::ptr(new GameView("data/gameViewPos.txt")));

	Maze::ptr maze = getGameEngine()->getGame().getMaze();
	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			Cell::ptr cell = maze->getCell(j, i);
			Point<double>& pos = myView->getGivenPosition("cellSize");
			cell->setRelSize(pos.x, pos.y); //not used for now
		}
	}
}

bool SGame::catchEvent(const sf::Event& ev)
{
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Right)
			{
				//if(isLocalHumanPlayer(getCurrentId())
				Message msg = MessageBuilder::clMove(Direction::EAST);
				sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
			}

			else if (ev.key.code == sf::Keyboard::Left)
			{
				Message msg = MessageBuilder::clMove(Direction::WEST);
				sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
			}

			else if (ev.key.code == sf::Keyboard::Up)
			{
				Message msg = MessageBuilder::clMove(Direction::NORTH);
				sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
			}

			else if (ev.key.code == sf::Keyboard::Down)
			{
				Message msg = MessageBuilder::clMove(Direction::SOUTH);
				sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
			}

			else if (ev.key.code == sf::Keyboard::Space)
			{
				Message msg = MessageBuilder::clEndTurn();
				sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
			}
		}
	//Game& game = getGameEngine()->getGame();
	//EntityManager entityManager = game.getEntityManager();

	//if (ev.Type == sf::Event::MouseMoved)
	//{
	//	if (entities.size() != 0)
	//	{
	//		entities.back()->setSelected(true);
	//		//Message msg = MessageBuilder::clCardToPlay(entities.back()->getId());
	//		//clientRequestTCP(msg);
	//	}
	//}
	////if(ev.Type == sf::Event::MouseMoved)
	////{
	////	std::vector<PtrGraphicEntity> allEntities = entityManager.getEntities();
	////	for(unsigned int i = 0; i < allEntities.size(); i++)
	////	{
	////		allEntities[i]->setSelected(false);
	////	}

	////	std::vector<PtrGraphicEntity> entities = 
	////		entityManager.getHoveredEntities(
	////			Point<double>(ev.MouseMove.X / getGraphicEngine()->getWindowSizeX(), 
	////						  ev.MouseMove.Y / getGraphicEngine()->getWindowSizeY())); //A modif
	////	if(entities.size() != 0)
	////	{
	////		entities.back()->setSelected(true);
	////		Message msg = MessageBuilder::clCardToPlay(entities.back()->getId());
	////		clientRequestTCP(msg);
	////	}
	////		
	////}

	//if (ev.Type == sf::Event::MouseButtonReleased)
	//{
	//	if (ev.MouseButton.Button == sf::Mouse::Left)
	//	{
	//	}
	//}
	return true;
}

void SGame::update()
{
	processQueue();

	Game& game = getGameEngine()->getGame();
	game.update(*this, getGraphicEngine()->getElapsedTime());

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

void SGame::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::SV_MOVE:
	{
		//Move player
		getSoundEngine()->playSound("move");
	}
	break;

	case Message::MessageType::SV_WALL:
	{
		//reveal the wall

		getSoundEngine()->playSound("wall");
	}
	break;

	case Message::MessageType::SV_NEW_TURN:
	{
		int id;
		if (!MessageBuilder::extractSvNewTurn(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		std::vector<Player::ptr> players = game.getPlayers();
		for (unsigned int i = 0; i < players.size(); i++)
		{
			if (id == players[i]->getId())
			{
				std::string sound = getTurnSound(i);
				if (sound != "")
					getSoundEngine()->pushSound(sound);
			}
		}
		
		//reveal the wall

		//getSoundEngine()->pushSound("endTurn");
	}
	break;

	case Message::MessageType::SV_DRAGOON_AWAKES:
	{
		//reveal the wall

		getSoundEngine()->pushSound("dragoonWakesUp");
	}
	break;

	case Message::MessageType::SV_DRAGOON_MOVES:
	{
		//reveal the wall

		getSoundEngine()->pushSound("dragoonMoves");
	}
	break;

	case Message::MessageType::SV_TAKE_TREASURE:
	{
		int id;
		if (!MessageBuilder::extractSvTakeTreasure(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		std::vector<Player::ptr> players = game.getPlayers();
		for (Player::ptr player : players)
		{
			player->setTreasure(false);
		}

		Player::ptr player = game.getPlayer(id);
		player->setTreasure(true);
		getSoundEngine()->pushSound("treasureFound");
	}
	break;

	case Message::MessageType::SV_GAME_WON:
	{
		int id;
		if (!MessageBuilder::extractSvGameWon(msg, id))
			return;

		getSoundEngine()->pushSound("win");
	}
	break;

	case Message::MessageType::SV_PLAYER_WOUNDED:
	{
		int id, numberLives;
		if (!MessageBuilder::extractSvPlayerWounded(msg, id, numberLives))
			return;

		Game& game = getGameEngine()->getGame();
		
		Player::ptr player = game.getPlayer(id);
		player->setNumberOfLives((Player::Lives)numberLives);


		getSoundEngine()->pushSound("dragoonAttacks");
	}
	break;

	default:
		break;
	}
}

std::string SGame::getTurnSound(int pos)
{
	if (pos < myTurnSoundByPlayerVectorPos.size() && pos >= 0)
		return myTurnSoundByPlayerVectorPos[pos];

	return "";
}