#include "Game.h"

#include "CellDefManager.h"
#include "CompleteMazeGenerator.h"
#include "EmptyMazeGenerator.h"
#include "PlayerDefManager.h"
#include "ResourceImageManager.h"
#include "ResourcesFile.h"
#include "SideDefManager.h"
#include "SoundBufferManager.h"
#include "TextureManager.h"
#include "tools/Rng.h"
#include "tools/Logger.h"


Game::Game()
:myMazeUnperfectPerc(20)
,myMazeSize(8)
,DRAGOON_NAME("Dragoon")
{
	ResourcesFile::getInstance()->read("./data/TexturesDat.dat", "TexturesDat");
	ResourcesFile::getInstance()->read("./data/SoundDat.dat", "SoundDat");

	TextureManager::getInstance()->preload();
	ResourceImageManager::getInstance()->preload();
	//SoundBufferManager::getInstance()->preload();
	CellDefManager::getInstance()->load("data/cellDef.dat");
	PlayerDefManager::getInstance()->load("data/playerDef.dat");
	SideDefManager::getInstance()->load("data/sideDef.dat");

	initDefaultMaze();

	//
	//{
	//	Player::ptr player(new Player(myManager.createNewId(), this));
	//	player->setSecretRoomPos(Point<int>(0, 0));
	//	player->setAbstractPosition(player->getSecretRoomPos());
	//	myManager.registerPlayer(player);
	//	player->setName("Yo");
	//	addLocalId(player->getId());
	//	myCurrentIdTurn = player->getId();
	//}

	//{
	//	Player::ptr player(new Player(myManager.createNewId(), this));
	//	player->setSecretRoomPos(Point<int>(3, 0));
	//	player->setAbstractPosition(player->getSecretRoomPos());
	//	myManager.registerPlayer(player);
	//	player->setName("Player 2");
	//	addLocalId(player->getId());
	//}

	//int xTres = 5; int yTres = 5;
	//Treasure::ptr treasure(new Treasure(myManager.createNewId(), this));
	//treasure->setAbstractPosition(xTres, yTres);
	//myManager.registerTreasure(treasure);

	//Dragoon::ptr dragoon(new Dragoon(myManager.createNewId(), this));
	//dragoon->setAbstractPosition(xTres, yTres);
	//dragoon->setName(DRAGOON_NAME);
	//myManager.registerDragoon(dragoon);
	//
}


Game::~Game()
{
}

void Game::initDefaultMaze()
{
	EmptyMazeGenerator gene;
	//CompleteMazeGenerator gene(30);

	createMaze(gene, myMazeSize, myMazeSize);
	//myMaze = gene.generate(8, 8);

	//int numberTileImages = CellDefManager::getInstance()->getNumberElements();
	//Rng rng;

	//for (int i = 0; i < myMaze->getSizeY(); i++)
	//{
	//	for (int j = 0; j < myMaze->getSizeX(); j++)
	//	{
	//		CellDef& def = getIndexCellDef(rng.random(0, numberTileImages - 1));
	//		Cell::ptr cell = myMaze->getCell(j, i);
	//		cell->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
	//		cell->setCurrentDrawnImage("main");
	//	}
	//}
}

Maze::ptr Game::createMaze(BaseMazeGenerator& generator, int x, int y)
{
	myMaze = generator.generate(x, y);
	int numberTileImages = CellDefManager::getInstance()->getNumberElements();
	Rng rng;

	for (int i = 0; i < myMaze->getSizeY(); i++)
	{
		for (int j = 0; j < myMaze->getSizeX(); j++)
		{
			CellDef& def = getIndexCellDef(rng.random(0, numberTileImages - 1));
			Cell::ptr cell = myMaze->getCell(j, i);
			cell->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
			cell->setCurrentDrawnImage("main");
		}
	}

	return myMaze;
}

PlayerDef& Game::getIndexPlayerDef(int index)
{
	PlayerDefManager::MapIterator it = PlayerDefManager::getInstance()->getIterator();
	int cpt = 0;

	while (cpt != index)
	{
		it = PlayerDefManager::getInstance()->next();
		cpt++;
	}

	return it->second;
}

CellDef& Game::getIndexCellDef(int index)
{
	CellDefManager::MapIterator it = CellDefManager::getInstance()->getIterator();
	int cpt = 0;

	while(cpt != index)
	{
		it = CellDefManager::getInstance()->next();
		cpt++;
	}

	return it->second;
}

void Game::update(GameState& state, unsigned int elapsedTime)
{
	std::vector<Entity::ptr> entities = getEntities();
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[i]->update(state, *this, elapsedTime);
	}
	
	getManager().update();
}

void Game::setTurnToFirstPlayer() 
{
	std::vector<Player::ptr> players = getPlayers();
	if(players.size() > 0)
		myCurrentIdTurn = players[0]->getId();
	else
	{
		ILogger::log() << "No players ! Cannot affect turn to first player.\n";
	}
}

int Game::nextEntityTurn()
{
	std::vector<Player::ptr> players = getPlayers();
	Dragoon::ptr dragoon = getDragoon();

	bool done = false;

	if (getCurrentIdTurn() == dragoon->getId())
	{
		myCurrentIdTurn = players[0]->getId();
		return myCurrentIdTurn;
	}


	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i]->getId() == getCurrentIdTurn())
		{
			if (i < players.size() - 1 && !players[i + 1]->hasLost())
			{
				myCurrentIdTurn = players[i + 1]->getId();
				return myCurrentIdTurn;
			}
		}
	}

	if(dragoon->isAwake())
		myCurrentIdTurn = dragoon->getId();
	else
		myCurrentIdTurn = players[0]->getId();

	return myCurrentIdTurn;
}

int Game::nextPlayerTurn()
{
	std::vector<Player::ptr> players = getPlayers();

	int id = nextEntityTurn();

	if (id == getDragoon()->getId())
		myCurrentIdTurn = players[0]->getId();

	return id;
}

bool Game::addLocalId(int id)
{
	for (unsigned int i = 0; i < myLocalIds.size(); i++)
	{
		if (myLocalIds[i] == id)
			return false;
	}

	myLocalIds.push_back(id);
	return true;
}

bool Game::isLocalId(int id) const
{
	for (unsigned int i = 0; i < myLocalIds.size(); i++)
	{
		if (myLocalIds[i] == id)
			return true;
	}

	return false;
}

Dragoon::ptr Game::getDragoon()
{
	return myManager.getDragoon();
}

Treasure::ptr Game::getTreasure()
{
	return myManager.getTreasure();
}

Entity::ptr Game::getEntity(int id)
{
	return myManager.getEntity(id);
}

std::vector<Entity::ptr> Game::getEntities()
{
	return myManager.getEntities();
}

Player::ptr Game::getPlayer(int id)
{
	return myManager.getPlayer(id);
}

std::vector<Player::ptr> Game::getPlayers()
{
	return myManager.getPlayers();
}

void Game::reset()
{
	initDefaultMaze();

	myManager.clear();
	myCurrentIdTurn = -1;

	myLocalIds.clear();

	myWinner = Player::ptr();
}

void Game::setup1PGame(const std::string& name)
{
	reset();

	Player::ptr player(new Player(myManager.createNewId(), this));
	//player->setSecretRoomPos(Point<int>(0, 0));
	PlayerDef& def = getIndexPlayerDef(0);
	player->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
	player->setCurrentDrawnImage("main");
	player->setAbstractPosition(player->getSecretRoomPos());
	myManager.registerPlayer(player);
	player->setName(name);
	addLocalId(player->getId());
	myCurrentIdTurn = player->getId();

	Dragoon::ptr dragoon(new Dragoon(myManager.createNewId(), this));
	//dragoon->setAbstractPosition(xTres, yTres);
	dragoon->setName(DRAGOON_NAME);
	myManager.registerDragoon(dragoon);

	Treasure::ptr treasure(new Treasure(myManager.createNewId(), this));
	myManager.registerTreasure(treasure);
}

void Game::setup2PGame(const std::string& p1, const std::string& p2)
{
	reset();

	{
		Player::ptr player(new Player(myManager.createNewId(), this));
		//player->setSecretRoomPos(Point<int>(0, 0));
		PlayerDef& def = getIndexPlayerDef(0);
		player->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
		player->setCurrentDrawnImage("main");
		player->setAbstractPosition(player->getSecretRoomPos());
		myManager.registerPlayer(player);
		player->setName(p1);
		addLocalId(player->getId());
		myCurrentIdTurn = player->getId();
	}

	{
		Player::ptr player(new Player(myManager.createNewId(), this));
		//player->setSecretRoomPos(Point<int>(0, 0));
		PlayerDef& def = getIndexPlayerDef(1);
		player->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
		player->setCurrentDrawnImage("main");
		player->setAbstractPosition(player->getSecretRoomPos());
		myManager.registerPlayer(player);
		player->setName(p2);
		addLocalId(player->getId());
	}

	Dragoon::ptr dragoon(new Dragoon(myManager.createNewId(), this));
	//dragoon->setAbstractPosition(xTres, yTres);
	dragoon->setName(DRAGOON_NAME);
	myManager.registerDragoon(dragoon);

	Treasure::ptr treasure(new Treasure(myManager.createNewId(), this));
	myManager.registerTreasure(treasure);
}