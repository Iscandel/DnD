#include "GameView.h"
#include "GameState.h"
//#include "Game.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"


#include "ResourceImageManager.h"

GameView::GameView(const std::string& path)
	:BaseGameView(path)
{
}


GameView::~GameView(void)
{
}

void GameView::loadViewPosition(const std::string& path)
{
	TextFile file(path);
	int nbElements = 0;

	file >> nbElements;
	for (int i = 0; i < nbElements; i++)
	{
		std::string string;
		double posX, posY;
		file >> string >> posX >> posY;
		myPositions.insert(std::make_pair(string, Point<double>(posX, posY)));
	}
}



void GameView::draw(GameState& state)
{
	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	//drawRect(state, sf::Color(128, 128, 128), sf::Vector2f(), sf::Vector2f(windowSizeX, windowSizeY));

	Game& game = state.getGameEngine()->getGame();
	Maze::ptr maze = game.getMaze();

	double x = 0;
	double y = 0;

	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");
	const Point<double>& boardOffset = getGivenPosition("boardOffset");
	const Point<double>& playerName = getGivenPosition("playerName");
	const Point<double>& livesAndSteps = getGivenPosition("livesAndSteps");

	//Black background
	drawRect(state, sf::Color::Black, sf::Vector2f(), sf::Vector2f(windowSizeX, windowSizeY));

	//Grey board
	drawRect(state, sf::Color(128, 128, 128), sf::Vector2f(), sf::Vector2f(0.60359375f * windowSizeX, windowSizeY));

	drawMaze(state, maze, windowSizeX, windowSizeY);

	auto players = game.getManager().getPlayers();
	for (Player::ptr player : players)
	{
		drawPlayer(state, player, windowSizeX, windowSizeY);
	}
	////Player 1
	//{
	//	//SecretRoom
	//	int id = 1; //to change
	//	auto player = game.getManager().getPlayer(id); //to change
	//	if (player)
	//	{
	//		const Point<int>& secretRoom = player->getSecretRoomPos();
	//		drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, sf::Color::Green);

	//		auto resource = ResourceImageManager::getInstance()->getResource(18);
	//		std::vector<Image> im; im.push_back(resource->getImage(0));
	//		sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
	//		sf::Vector2f pos((player->getAbstractX() * (cellSize.x + wallSizeVert.x) + boardOffset.x )* windowSizeX, 
	//			(player->getAbstractY() * (cellSize.y + wallSizeHoriz.y) + boardOffset.y) * windowSizeY);
	//		drawImage(state, im, pixelSize, pos, 0.f);
	//	}
	//}

	////Player 2
	//{
	//	//SecretRoom
	//	int id = 2; //to change
	//	auto player = game.getManager().getPlayer(id); //to change
	//	if (player)
	//	{
	//		const Point<int>& secretRoom = player->getSecretRoomPos();
	//		drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, sf::Color::Yellow);

	//		auto resource = ResourceImageManager::getInstance()->getResource(21);
	//		std::vector<Image> im; im.push_back(resource->getImage(0));
	//		sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
	//		sf::Vector2f pos((player->getAbstractX() * (cellSize.x + wallSizeVert.x) + boardOffset.x)* windowSizeX,
	//			(player->getAbstractY() * (cellSize.y + wallSizeHoriz.y) + boardOffset.y) * windowSizeY);
	//		drawImage(state, im, pixelSize, pos, 0.f);
	//	}
	//}

	//Dragoon (debug)
	{
		//auto resource = ResourceImageManager::getInstance()->getResource(20);
		//std::vector<Image> im; im.push_back(resource->getImage(0));
		//sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
		//auto dragoon = game.getDragoon(); //to change
		//sf::Vector2f pos((dragoon->getAbstractX() * (cellSize.x + wallSizeVert.x) + boardOffset.x) * windowSizeX, 
		//	(dragoon->getAbstractY() * (cellSize.y + wallSizeHoriz.y) + boardOffset.y) * windowSizeY);
		//drawImage(state, im, pixelSize, pos, 0.f);
	}

	auto entity = game.getEntity(game.getCurrentIdTurn());
	if(entity)
		drawPlayerName(state, entity, playerName.x, playerName.y, windowSizeX, windowSizeY);
	else
	{
		drawPlayerName(state, "Other:", false, playerName.x, playerName.y, windowSizeX, windowSizeY);
	}

	auto player = game.getPlayer(game.getCurrentIdTurn());
	if (player && game.isLocalId(player->getId()))
		drawLivesAndSteps(state, player, livesAndSteps.x, livesAndSteps.y, windowSizeX, windowSizeY);
}

void GameView::drawPlayer(GameState& state, Player::ptr player, int windowSizeX, int windowSizeY)
{
	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");
	const Point<double>& boardOffset = getGivenPosition("boardOffset");
	
	const Point<int>& secretRoom = player->getSecretRoomPos();
	drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, getSecretRoomColorById(player->getId()));

	std::vector<Image> im = player->getCurrentImages();
	//auto resource = ResourceImageManager::getInstance()->getResource(18);
	//std::vector<Image> im; im.push_back(resource->getImage(0));
	sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
	sf::Vector2f pos((player->getAbstractX() * (cellSize.x + wallSizeVert.x) + boardOffset.x)* windowSizeX,
		(player->getAbstractY() * (cellSize.y + wallSizeHoriz.y) + boardOffset.y) * windowSizeY);
	drawImage(state, im, pixelSize, pos, 0.f);
}

sf::Color GameView::getSecretRoomColorById(int id)
{
	std::map<int, sf::Color>::iterator it = mySecretRoomColorById.find(id);
	if (it != mySecretRoomColorById.end())
	{
		return it->second;
	}

	return sf::Color::Black;
}

//Maze::ptr maze = state.getGameEngine()->getGame().getMaze();
//sf::Sprite sp;
//
////sp.setTexture(textureFond);
////sp.setScale(80.f / textureFond.getSize().x, 80.f / textureFond.getSize().y);
//int x = 0;
//int y = 0;

//
//sf::Sprite spWallRot;
//sf::Sprite spWall;
////spWallRot.setTexture(textureMur);
////spWall.setTexture(textureMur);
//
//for (int i = 0; i < maze->getSizeY(); i++)
//{
//	for (int j = 0; j < maze->getSizeX(); j++)
//	{
//		Cell::ptr cell = maze->getCell(j, i);
//		
//		//sp.setPosition(x, y);

//		std::vector<Image>& resource = cell->getCurrentImages();
//		for (unsigned int k = 0; k < resource.size(); k++)
//		{
//			PtrTexture texture = resource[k].getResourceTexture()->getTexture();
//			sp.setTexture(*texture);
//			IntRect rect = resource[k].getRect();
//			if (rect.width > 0 && rect.height > 0)
//			{
//				sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//				sp.setTextureRect(sfRect);
//			}

//			sp.setScale(80.f / texture->getSize().x, 80.f / texture->getSize().y);
//			//sp.setScale((cell->getRelSizeX() * (double)1024) / 300.,//rect.width,
//			//(cell->getRelSizeY() * (double)768) / 300.);//rect.height);
//			//rotation is in clockwise order for SFML
//			//sp.setRotation(-cards[j]->getRotation());

//			sp.setPosition(x, y);//cards[j]->getX() * windowSizeX, cards[j]->getY() * windowSizeY);
//			state.getGraphicEngine()->draw(sp);
//		}


//		sf::Color shadowCol(50, 50, 50);
//		drawRect(state, shadowCol, sf::Vector2f(x, y), sf::Vector2f(80, 2));
//		drawRect(state, shadowCol, sf::Vector2f(x, y), sf::Vector2f(2, 80));
//		sf::Color lightCol(170, 170, 170);
//		drawRect(state, lightCol, sf::Vector2f(x, y + 78), sf::Vector2f(80, 2));
//		drawRect(state, lightCol, sf::Vector2f(x + 78, y), sf::Vector2f(2, 80));

//		if (cell->getSide(Direction::EAST)->getType() == Side::WALL)
//		{			
//			
//			////spWallRot.setOrigin(textureMur.getSize().x / 2.f, textureMur.getSize().y / 2.f);
//			//spWallRot.setRotation(90.f);
//			////		spWallRot.setOrigin(0, 0);		
//			//spWallRot.setScale(80.f / textureMur.getSize().x, 20.f / textureMur.getSize().y);
//			//spWallRot.setPosition(x + 80 + 20, y);
//			
//			//
//			Side::ptr side = cell->getSide(Direction::EAST);
//			std::vector<Image>& resource = side->getCurrentImages();
//			for (unsigned int k = 0; k < resource.size(); k++)
//			{
//				PtrTexture texture = resource[k].getResourceTexture()->getTexture();
//				spWallRot.setTexture(*texture);
//				IntRect rect = resource[k].getRect();
//				if (rect.width > 0 && rect.height > 0)
//				{
//					sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//					spWallRot.setTextureRect(sfRect);
//				}
//				spWallRot.setRotation(90.f);
//				//		spWallRot.setOrigin(0, 0);		
//				spWallRot.setScale(100.f / texture->getSize().x, 20.f / texture->getSize().y);
//				spWallRot.setPosition(x + 80 + 20, y - 10);

//				state.getGraphicEngine()->draw(spWallRot);
//			}
//			//
//		}
//		if (cell->getSide(Direction::SOUTH)->getType() == Side::WALL)
//		{
//			//spWall.setScale(80.f / textureMur.getSize().x, 20.f / textureMur.getSize().y);
//			//spWall.setPosition(x, y + 80);
//			//state.getGraphicEngine()->draw(spWall);

//			//
//			Side::ptr side = cell->getSide(Direction::SOUTH);
//			std::vector<Image>& resource = side->getCurrentImages();
//			for (unsigned int k = 0; k < resource.size(); k++)
//			{
//				PtrTexture texture = resource[k].getResourceTexture()->getTexture();
//				spWall.setTexture(*texture);
//				IntRect rect = resource[k].getRect();
//				if (rect.width > 0 && rect.height > 0)
//				{
//					sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//					spWall.setTextureRect(sfRect);
//				}

//				spWall.setScale(100.f / texture->getSize().x, 20.f / texture->getSize().y);
//				spWall.setPosition(x - 10, y + 80);
//				state.getGraphicEngine()->draw(spWall);
//			}
//			//
//		}

//		x += 80 + 20;
//	}
//	x = 0;
//	y += 80 + 20;
//}