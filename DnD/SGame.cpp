#include "SGame.h"

#include "DraggableImage.h"
#include "GameEngine.h"
#include "GameView.h"
#include "GraphicEngine.h"
#include "MessageBuilder.h"
#include "NetworkEngine.h"
#include "SGameWon.h"
#include "SoundEngine.h"
#include "TextureManager.h"
#include "tools/Logger.h"
#include "ResourcesFile.h"

#include "Gaia/addFactory.h"
#include "Gaia/widgetRenderers/ImageBoxRenderer.h"
#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

#include "CompleteMazeGenerator.h"

SGame::SGame(void)
{
}


SGame::~SGame(void)
{
}

void SGame::init()
{	
	setView(View::ptr(new GameView("data/gameViewPos.txt")));

	gaia::GuiManager::getInstance()->clean();
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiGame.xml");

	gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));

	initDraggable("./data/textures/dragoon.png", "dragoonImage", "draggableDragoon");
	initDraggable("./data/textures/treasure.png", "treasureImage", "draggableTreasure");

	//gaia::PtrWidget dragDrag = manager->createWidget("DraggableImage", "draggableDragoon");


	

	Game& game = getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();
	for (unsigned int i = 0; i < players.size(); i++)	
	{
		if (i == 0)
			myTurnSoundByPlayerId[players[i]->getId()] = "p1NewTurn";
		else if (i == 1)
			myTurnSoundByPlayerId[players[i]->getId()] = "p2NewTurn";
		else
			ILogger::log() << "Turn tunes : not designed for more than 2P\n";
	}

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
	if (!gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev)))
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
	return false;
}

void SGame::update()
{
	processQueue();

	Game& game = getGameEngine()->getGame();
	game.update(*this, getGraphicEngine()->getElapsedTime());

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());

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
		int cellX, cellY;
		Direction direction;
		if (!MessageBuilder::extractSvWall(msg, cellX, cellY, direction))
			return;

		Game& game = getGameEngine()->getGame();
		Maze::ptr maze = game.getMaze();
		Cell::ptr cell = maze->getCell(cellX, cellY);
		cell->getSide(direction)->revealSide();

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
		std::string sound = getTurnSound(id);
		if (sound != "")
			getSoundEngine()->pushSound(sound);
		
		//reveal the wall

		//getSoundEngine()->pushSound("endTurn");
	}
	break;

	case Message::MessageType::SV_DRAGOON_AWAKES:
	{
		getSoundEngine()->pushSound("dragoonWakesUp");
	}
	break;

	case Message::MessageType::SV_DRAGOON_MOVES:
	{
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

	case Message::MessageType::SV_PLAYER_TAKES_TREASURE_FROM_PLAYER:
	{
		int id;
		if (!MessageBuilder::extractSvPlayerTakesTreasureFromPlayer(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		std::vector<Player::ptr> players = game.getPlayers();
		for (Player::ptr player : players)
		{
			player->setTreasure(false);
		}

		std::string sound = getTurnSound(id);
		if (sound != "")
			getSoundEngine()->pushSound(sound);

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

		Game& game = getGameEngine()->getGame();
		Player::ptr winner = game.getPlayer(id);
		game.setWinner(winner);

		getSoundEngine()->pushSound("win");
		pushClientGameState(GameState::ptr(new SGameWon));
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

std::string SGame::getTurnSound(int id)
{
	std::map<int, std::string>::iterator it = myTurnSoundByPlayerId.find(id);
	if (it != myTurnSoundByPlayerId.end())
		return it->second;

	return "";
}

void SGame::initDraggable(const std::string& imageId, const std::string& imageName, const std::string& widgetName)
{
	gaia::GuiManager* manager = gaia::GuiManager::getInstance();

	long int size = 0;
	const bool freeMem = true;
	char* data = ResourcesFile::getInstance()->getFile(imageId, "TexturesDat", &size);
	sf::Texture* tex = new sf::Texture;
	tex->loadFromMemory(data, size);
	delete[] data;

	gaia::Image im(gaia::PtrTexture(new gaia::SFMLTexture(tex)), imageName);
	boost::shared_ptr<DraggableImage> dragDrag = manager->getWidget<DraggableImage>(widgetName);
	manager->getWidget<DraggableImage>(widgetName)->setWidgetRenderer(new gaia::ImageBoxRenderer);
	manager->getWidget<DraggableImage>(widgetName)->setImage(im);
}