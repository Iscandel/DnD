#include "Game.h"

#include "CellDefManager.h"
#include "CompleteMazeGenerator.h"
#include "ResourceImageManager.h"
#include "ResourcesFile.h"
#include "SideDefManager.h"
#include "TextureManager.h"
#include "tools/Rng.h"


Game::Game()
{
	ResourcesFile::getInstance()->read("./data/TexturesDat.dat", "TexturesDat");

	TextureManager::getInstance()->preload();
	ResourceImageManager::getInstance()->preload();
	CellDefManager::getInstance()->load("data/cellDef.dat");
	SideDefManager::getInstance()->load("data/sideDef.dat");

	initMaze();
}


Game::~Game()
{
}

void Game::initMaze()
{
	CompleteMazeGenerator gene(30);
	myMaze = gene.generate(8, 8);

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
