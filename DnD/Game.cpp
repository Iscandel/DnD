#include "Game.h"

#include "CellDefManager.h"
#include "CompleteMazeGenerator.h"
#include "EmptyMazeGenerator.h"
#include "ResourceImageManager.h"
#include "ResourcesFile.h"
#include "SideDefManager.h"
#include "SoundBufferManager.h"
#include "TextureManager.h"
#include "tools/Rng.h"


Game::Game()
:myMazeUnperfectPerc(80)
,myMazeSize(8)
{
	ResourcesFile::getInstance()->read("./data/TexturesDat.dat", "TexturesDat");
	ResourcesFile::getInstance()->read("./data/SoundDat.dat", "SoundDat");

	TextureManager::getInstance()->preload();
	ResourceImageManager::getInstance()->preload();
	//SoundBufferManager::getInstance()->preload();
	CellDefManager::getInstance()->load("data/cellDef.dat");
	SideDefManager::getInstance()->load("data/sideDef.dat");

	initDefaultMaze();

	//
	{
		Player::ptr player(new Player(myManager.createNewId(), this));
		player->setSecretRoomPos(Point<int>(0, 0));
		player->setAbstractPosition(player->getSecretRoomPos());
		myManager.registerPlayer(player);
		player->setName("Yo");
		myCurrentIdTurn = player->getId();
	}

	{
		Player::ptr player(new Player(myManager.createNewId(), this));
		player->setSecretRoomPos(Point<int>(3, 0));
		player->setAbstractPosition(player->getSecretRoomPos());
		myManager.registerPlayer(player);
		player->setName("Player 2");
	}

	int xTres = 5; int yTres = 5;
	Treasure::ptr treasure(new Treasure(myManager.createNewId(), this));
	treasure->setAbstractPosition(xTres, yTres);
	myManager.registerTreasure(treasure);

	Dragoon::ptr dragoon(new Dragoon(myManager.createNewId(), this));
	dragoon->setAbstractPosition(xTres, yTres);
	myManager.registerDragoon(dragoon);
	//


	//myManager.getEntity(0)->setPos(0, 0); //to change getEntity
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
	
	if(id == getDragoon()->getId())
		myCurrentIdTurn = players[0]->getId();

	return id;
}

Dragoon::ptr Game::getDragoon()
{
	return myManager.getDragoon();
}

Treasure::ptr Game::getTreasure()
{
	return myManager.getTreasure();
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