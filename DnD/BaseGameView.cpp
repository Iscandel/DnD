#include "BaseGameView.h"

#include "GameState.h"
//#include "Game.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"


#include "ResourceImageManager.h"

std::map<int, sf::Color> BaseGameView::mySecretRoomColorById;

BaseGameView::BaseGameView(const std::string& path)
{
	loadViewPosition(path);
}


BaseGameView::~BaseGameView(void)
{
}

void BaseGameView::loadViewPosition(const std::string& path)
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

void BaseGameView::initializeSecretRoomColor(GameState& state)
{
	Rng rng;
	Game& game = state.getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();
	for (Player::ptr player : players)
	{
		sf::Color col(rng.random(0, 255), rng.random(0, 255), rng.random(0, 255));
		mySecretRoomColorById[player->getId()] = col;
	}
}

void BaseGameView::drawMaze(GameState& state, Maze::ptr maze, int windowSizeX, int windowSizeY)
{
	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");
	const Point<double>& boardOffset = getGivenPosition("boardOffset");

	double x = 0;
	double y = 0;

	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			Cell::ptr cell = maze->getCell(j, i);

			std::vector<Image>& resource = cell->getCurrentImages();
			sf::Vector2f pixelSize(cellSize.x * (float)windowSizeX, cellSize.y * (float)windowSizeY);
			sf::Vector2f pos((boardOffset.x + x) * windowSizeX, (boardOffset.y + y) * windowSizeY);
			drawImage(state, resource, pixelSize, pos, 0.f);

			drawCellShadows(state, x, y, windowSizeX, windowSizeY);

			Side::ptr sideEast = cell->getSide(Direction::EAST);
			if (sideEast->getType() == Side::WALL && sideEast->isRevealed())
			{
				std::vector<Image>& resource = sideEast->getCurrentImages();
				sf::Vector2f pixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
				sf::Vector2f pos((boardOffset.x + x + cellSize.x + wallSizeVert.x) * windowSizeX, (boardOffset.y + y - wallSizeHoriz.y / 2.) * windowSizeY);
				drawImage(state, resource, pixelSize, pos, 90.f);
			}

			Side::ptr sideSouth = cell->getSide(Direction::SOUTH);
			if (sideSouth->getType() == Side::WALL && sideSouth->isRevealed())
			{
				std::vector<Image>& resource = sideSouth->getCurrentImages();
				sf::Vector2f pixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
				sf::Vector2f pos((boardOffset.x + x - wallSizeHoriz.y / 2.) * windowSizeX, (boardOffset.y + y + cellSize.y) * windowSizeY);
				drawImage(state, resource, pixelSize, pos, 0.f);
			}

			x += cellSize.x + wallSizeVert.x;
		}
		x = 0.;
		y += cellSize.y + wallSizeHoriz.y;
	}
}
void BaseGameView::drawRect(GameState& state, const sf::Color& col, const sf::Vector2f& pos, const sf::Vector2f& size)
{
	sf::RectangleShape rect;
	rect.setFillColor(col);
	rect.setPosition(pos);
	rect.setSize(size);
	state.getGraphicEngine()->draw(rect);
}

void BaseGameView::drawCellShadows(GameState& state, double x, double y, int windowSizeX, int windowSizeY)
{
	sf::Color shadowCol(50, 50, 50);
	const Point<double>& shadowSize = getGivenPosition("shadowSize");
	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& boardOffset = getGivenPosition("boardOffset");

	//horiz
	drawRect(state,
		shadowCol,
		sf::Vector2f((boardOffset.x + x) * windowSizeX, (boardOffset.y + y) * windowSizeY),
		sf::Vector2f(cellSize.x * windowSizeX, shadowSize.y * windowSizeY));
	//vert
	drawRect(state,
		shadowCol,
		sf::Vector2f((boardOffset.x + x) * windowSizeX, (boardOffset.y + y) * windowSizeY),
		sf::Vector2f(shadowSize.x * windowSizeX, cellSize.y * windowSizeY));

	sf::Color lightCol(170, 170, 170);
	//horiz
	drawRect(state,
		lightCol,
		sf::Vector2f((boardOffset.x + x) * windowSizeX, (boardOffset.y + y + cellSize.y - shadowSize.y) * windowSizeY),
		sf::Vector2f(cellSize.x * windowSizeX, shadowSize.y * windowSizeY));
	//vert
	drawRect(state,
		lightCol,
		sf::Vector2f((boardOffset.x + x + cellSize.x - shadowSize.x) * windowSizeX, (boardOffset.y + y) * windowSizeY),
		sf::Vector2f(shadowSize.x * windowSizeX, cellSize.y * windowSizeY));
}

void BaseGameView::drawImage(GameState& state, std::vector<Image>& resource, const sf::Vector2f& pixelSize, const sf::Vector2f& pos, float rotation)
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

void BaseGameView::drawPlayerName(GameState& state, Entity::ptr player, float x, float y, int windowSizeX, int windowSizeY)
{
	Game& game = state.getGameEngine()->getGame();
	drawPlayerName(state, player->getName() + " turn :", game.isLocalId(player->getId()), x, y, windowSizeX, windowSizeY);
}

void BaseGameView::drawPlayerName(GameState& state, const std::string& str, bool localId, float x, float y, int windowSizeX, int windowSizeY)
{
	Game& game = state.getGameEngine()->getGame();

	sf::Text text;
	text.setFont(myFont);
	text.setString(str);

	double ratioY = windowSizeY / 768.;
	text.setCharacterSize(60 * ratioY);
	text.setFillColor(sf::Color::White);
	text.setPosition(x * windowSizeX, y * windowSizeY);
	state.getGraphicEngine()->draw(text);

	sf::FloatRect rect = text.getGlobalBounds();
	float relHeight = rect.height / windowSizeY;

	text.setPosition(x * windowSizeX, (y + relHeight) * windowSizeY);
	if (localId)
	{
		text.setString("Play !");
		text.setFillColor(sf::Color::Green);
		state.getGraphicEngine()->draw(text);
	}
	else
	{
		text.setString("Wait !");
		text.setFillColor(sf::Color::Red);
		state.getGraphicEngine()->draw(text);
	}
}

void BaseGameView::drawLivesAndSteps(GameState& state, Player::ptr player, float x, float y, int windowSizeX, int windowSizeY)
{
	Game& game = state.getGameEngine()->getGame();

	sf::Text text;
	text.setFont(myFont);
	text.setString("Lives: " + tools::numToString(player->getNumberOfLives()));

	double ratioY = windowSizeY / 768.;
	text.setCharacterSize(60 * ratioY);
	text.setFillColor(sf::Color::White);
	text.setPosition(x * windowSizeX, y * windowSizeY);
	state.getGraphicEngine()->draw(text);

	sf::FloatRect rect = text.getGlobalBounds();
	float relHeight = rect.height / windowSizeY;

	text.setPosition(x * windowSizeX, (y + relHeight) * windowSizeY);
	text.setString("Steps: " + tools::numToString(player->getCurrentStepsRemaining()));
	state.getGraphicEngine()->draw(text);
}

void BaseGameView::drawSecretRoom(GameState& state, int x, int y, int windowSizeX, int windowSizeY, const sf::Color& fill)
{
	const Point<double>& cellSize = getGivenPosition("cellSize");
	const Point<double>& wallSizeHoriz = getGivenPosition("wallSizeHoriz");
	const Point<double>& wallSizeVert = getGivenPosition("wallSizeVert");
	const Point<double>& boardOffset = getGivenPosition("boardOffset");

	sf::Vector2f cellPixelSize(wallSizeHoriz.x * windowSizeX, wallSizeHoriz.y * windowSizeY);
	sf::Vector2f pos(x * (cellSize.x + wallSizeVert.x), y * (cellSize.y + wallSizeHoriz.y));

	double ratio = 0.7;
	sf::Vector2f roomSize = sf::Vector2f(ratio * cellSize.x, ratio * cellSize.y);

	sf::Vector2f finalPos((boardOffset.x + pos.x + cellSize.x / 2.f - roomSize.x / 2.f)  * windowSizeX,
		(boardOffset.y + pos.y + cellSize.y / 2.f - roomSize.y / 2.f)  * windowSizeY);
	sf::RectangleShape rect;
	rect.setFillColor(fill);
	rect.setPosition(finalPos);
	rect.setSize(sf::Vector2f(roomSize.x * windowSizeX, roomSize.y * windowSizeY));
	rect.setOutlineColor(sf::Color(10, 50, 10));
	rect.setOutlineThickness(4.f);
	state.getGraphicEngine()->draw(rect);
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