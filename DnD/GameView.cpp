#include "GameView.h"
#include "GameState.h"
//#include "Game.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"


#include "ResourceImageManager.h"

GameView::GameView(const std::string& path)
{
	loadViewPosition(path);

	//CompleteMazeGenerator gene(30);
	//maze = gene.generate(8, 8);
	//std::cout << *(maze.get());

	//if (!textureMur.loadFromFile("D:\\C et CPP\\Applications\\DnD\\DnD\\data\\wall.png"))
	//	std::cout << "fdsjhfskql\n";

	//if(!textureFond.loadFromFile("D:\\C et CPP\\Applications\\DnD\\DnD\\data\\textures\\tile2.png"))
	//	std::cout << "zraerazz\n";
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

	drawRect(state, sf::Color(128, 128, 128), sf::Vector2f(), sf::Vector2f(windowSizeX, windowSizeY));

	Game& game = state.getGameEngine()->getGame();
	Maze::ptr maze = game.getMaze();

	double x = 0;
	double y = 0;

	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");

	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			Cell::ptr cell = maze->getCell(j, i);

			std::vector<Image>& resource = cell->getCurrentImages();
			sf::Vector2f pixelSize(cellSize.x * (float)windowSizeX, cellSize.y * (float)windowSizeY);
			sf::Vector2f pos(x * windowSizeX, y * windowSizeY);
			drawImage(state, resource, pixelSize, pos, 0.f);

			drawCellShadows(state, x, y, windowSizeX, windowSizeY);

			Side::ptr sideEast = cell->getSide(Direction::EAST);
			if (sideEast->getType() == Side::WALL && sideEast->isRevealed())
			{
				std::vector<Image>& resource = sideEast->getCurrentImages();
				sf::Vector2f pixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
				sf::Vector2f pos((x + cellSize.x + wallSizeVert.x) * windowSizeX, (y - wallSizeHoriz.y / 2.) * windowSizeY);
				drawImage(state, resource, pixelSize, pos, 90.f);
			}

			Side::ptr sideSouth = cell->getSide(Direction::SOUTH);
			if (sideSouth->getType() == Side::WALL && sideSouth->isRevealed())
			{
				std::vector<Image>& resource = sideSouth->getCurrentImages();
				sf::Vector2f pixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
				sf::Vector2f pos((x - wallSizeHoriz.y / 2.) * windowSizeX, (y + cellSize.y) * windowSizeY);
				drawImage(state, resource, pixelSize, pos, 0.f);
			}

			x += cellSize.x + wallSizeVert.x;
		}
		x = 0.;
		y += cellSize.y + wallSizeHoriz.y;
	}

	

	//Player 1
	{
		//SecretRoom
		int id = 1; //to change
		auto player = game.getManager().getPlayer(id); //to change
		const Point<int>& secretRoom = player->getSecretRoomPos();
		drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, sf::Color::Green);

		auto resource = ResourceImageManager::getInstance()->getResource(18);
		std::vector<Image> im; im.push_back(resource->getImage(0));
		sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
		sf::Vector2f pos(player->getAbstractX() * (cellSize.x + wallSizeVert.x) * windowSizeX, player->getAbstractY() * (cellSize.y + wallSizeHoriz.y) * windowSizeY);
		drawImage(state, im, pixelSize, pos, 0.f);
	}

	//Player 2
	{
		//SecretRoom
		int id = 2; //to change
		auto player = game.getManager().getPlayer(id); //to change
		const Point<int>& secretRoom = player->getSecretRoomPos();
		drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, sf::Color::Yellow);

		auto resource = ResourceImageManager::getInstance()->getResource(21);
		std::vector<Image> im; im.push_back(resource->getImage(0));
		sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
		sf::Vector2f pos(player->getAbstractX() * (cellSize.x + wallSizeVert.x) * windowSizeX, player->getAbstractY() * (cellSize.y + wallSizeHoriz.y) * windowSizeY);
		drawImage(state, im, pixelSize, pos, 0.f);
	}

	//Dragoon (debug)
	{
		auto resource = ResourceImageManager::getInstance()->getResource(20);
		std::vector<Image> im; im.push_back(resource->getImage(0));
		sf::Vector2f pixelSize(cellSize.x * windowSizeX, cellSize.y * windowSizeY);
		auto dragoon = game.getDragoon(); //to change
		sf::Vector2f pos(dragoon->getAbstractX() * (cellSize.x + wallSizeVert.x) * windowSizeX, dragoon->getAbstractY() * (cellSize.y + wallSizeHoriz.y) * windowSizeY);
		drawImage(state, im, pixelSize, pos, 0.f);
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


	////Players
	//int number = game.getNumberPlayers();
	//for (int i = 0; i < number; i++)
	//{
	//	PtrPlayer player = game.getPlayerByPosition(i);
	//	const std::vector<PtrCard>& cards = player->getCards();

	//	//std::cout << (static_cast<CardHandler<Player>* >(player)) << std::endl;
	//	drawCards(state, cards);
	//	PtrTeam team = game.getTeam(player->getId());
	//	sf::String string(tools::numToString(team->getTeamId()) + ". " + player->getName());
	//	sf::Text text(string);
	//	text.SetCharacterSize(15);
	//	Point<double> pos = getGivenPosition("4p_p" + tools::numToString(i + 1) + "Name");
	//	text.SetPosition(pos.x * windowSizeX, pos.y * windowSizeY);
	//	state.getGraphicEngine()->draw(text);
	//}

	////Table (no ref)
	//std::vector<PtrCard> cards = game.getTable().getCards();
	//drawCards(state, cards);

	////TrickSet (no ref)
	//cards = game.getTrickSet().getCards();
	//drawCards(state, cards);
}

void GameView::drawRect(GameState& state, const sf::Color& col, const sf::Vector2f& pos, const sf::Vector2f& size)
{
	sf::RectangleShape rect;
	rect.setFillColor(col);
	rect.setPosition(pos);
	rect.setSize(size);
	state.getGraphicEngine()->draw(rect);
}

void GameView::drawCellShadows(GameState& state, double x, double y, int windowSizeX, int windowSizeY)
{
	sf::Color shadowCol(50, 50, 50);
	const Point<double>& shadowSize = getGivenPosition("shadowSize");
	const Point<double>& cellSize = getGivenPosition("cellSize");

	//horiz
	drawRect(state, 
		shadowCol, 
		sf::Vector2f(x * windowSizeX, y * windowSizeY), 
		sf::Vector2f(cellSize.x * windowSizeX, shadowSize.y * windowSizeY));
	//vert
	drawRect(state, 
		shadowCol, 
		sf::Vector2f(x * windowSizeX, y * windowSizeY), 
		sf::Vector2f(shadowSize.x * windowSizeX, cellSize.y * windowSizeY));

	sf::Color lightCol(170, 170, 170);
	//horiz
	drawRect(state, 
		lightCol, 
		sf::Vector2f(x * windowSizeX, (y  + cellSize.y - shadowSize.y) * windowSizeY), 
		sf::Vector2f(cellSize.x * windowSizeX, shadowSize.y * windowSizeY));
	//vert
	drawRect(state, 
		lightCol, 
		sf::Vector2f((x + cellSize.x - shadowSize.x) * windowSizeX, y * windowSizeY), 
		sf::Vector2f(shadowSize.x * windowSizeX, cellSize.y * windowSizeY));
}

void GameView::drawImage(GameState& state, std::vector<Image>& resource, const sf::Vector2f& pixelSize, const sf::Vector2f& pos, float rotation)
{
	sf::Sprite sprite;
	for (unsigned int k = 0; k < resource.size(); k++)
	{
		PtrTexture texture = resource[k].getResourceTexture()->getTexture();
		sprite.setTexture(*texture);
		IntRect rect = resource[k].getRect();
		//if (rect.width > 0 && rect.height > 0)
		{
			sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
			sprite.setTextureRect(sfRect);
		}
		sprite.setRotation(rotation);
		//spWallRot.setOrigin(0, 0);		
		sprite.setScale(pixelSize.x / rect.width, pixelSize.y / rect.height);
		sprite.setPosition(pos);

		state.getGraphicEngine()->draw(sprite);
	}
}

void GameView::drawSecretRoom(GameState& state, int x, int y, int windowSizeX, int windowSizeY, const sf::Color& fill)
{
	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");

	sf::Vector2f cellPixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
	sf::Vector2f pos(x * (cellSize.x + wallSizeVert.x), y * (cellSize.y + wallSizeHoriz.y));

	double ratio = 0.7;
	sf::Vector2f roomSize = sf::Vector2f(ratio * cellSize.x, ratio * cellSize.y);

	sf::Vector2f finalPos((pos.x + cellSize.x / 2.f - roomSize.x / 2.f)  * windowSizeX, (pos.y + cellSize.y / 2.f - roomSize.y / 2.f)  * windowSizeY);
	sf::RectangleShape rect;
	rect.setFillColor(fill);
	rect.setPosition(finalPos);
	rect.setSize(sf::Vector2f(roomSize.x * windowSizeX, roomSize.y * windowSizeY));
	rect.setOutlineColor(sf::Color(10, 50, 10));
	rect.setOutlineThickness(4.f);
	state.getGraphicEngine()->draw(rect);
}

//void GameView::drawCards(GameState& state, const std::vector<PtrCard>& cards)
//{
//	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
//	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();
//	for (unsigned int j = 0; j < cards.size(); j++)
//	{
//		sf::Sprite sp;
//		//PtrResourceImage resource;
//		//if(i == 0)
//		//	resource = cards[j]->getCurrentImage(); //Il faudrait un vecteur de rect et la texture associée (cas multi images). Ou alors renvoyer un vec + 2ème fonction std::vec<int> getCurrentNumImages() 
//		//else
//		//	resource = cards[j]->getImageBack();
//		std::vector<Image>& resource = cards[j]->getCurrentImages();
//		//if(resource)
//		for (unsigned int k = 0; k < resource.size(); k++)
//		{
//			PtrTexture texture = resource[k].getResourceTexture()->getTexture();
//			//PtrTexture texture = resource->getResourceTexture()->getTexture(); 
//			//Optimization
//			//if(k == 0 || (k > 0 && resource[k].getTextureId() != resource[k - 1].getTextureId()))
//			{
//				sp.SetTexture(*texture);
//			}
//
//			IntRect rect = resource[k].getRect();
//			//IntRect rect = resource->getImage().getRect();
//			sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//			sp.SetTextureRect(sfRect);
//			sp.SetScale((cards[j]->getRelSizeX() * (double)windowSizeX) / rect.width,
//				(cards[j]->getRelSizeY() * (double)windowSizeY) / rect.height);
//			//rotation is in clockwise order for SFML
//			sp.SetRotation(-cards[j]->getRotation());
//
//			sp.SetPosition(cards[j]->getX() * windowSizeX, cards[j]->getY() * windowSizeY);
//
//			if (cards[j]->isSelected())
//			{
//				sp.SetColor(sf::Color(100, 100, 200));
//			}
//
//			state.getGraphicEngine()->draw(sp);
//		}
//	}
//}