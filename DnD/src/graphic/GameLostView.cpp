#include "GameLostView.h"


#include "gameState/GameState.h"
//#include "Game.h"
#include "resources/TextureManager.h"
#include "game/GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"

GameLostView::GameLostView()
{
}


GameLostView::~GameLostView()
{
	//loadViewPosition(path);
}

//void GameWonView::loadViewPosition(const std::string& path)
//{
//	TextFile file(path);
//	int nbElements = 0;
//
//	file >> nbElements;
//	for (int i = 0; i < nbElements; i++)
//	{
//		std::string string;
//		double posX, posY;
//		file >> string >> posX >> posY;
//		myPositions.insert(std::make_pair(string, Point<double>(posX, posY)));
//	}
//}

void GameLostView::draw(GameState& state)
{
	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	Game& game = state.getGameEngine()->getGame();
	Maze::ptr maze = game.getMaze();

	sf::RectangleShape background(sf::Vector2f((float)windowSizeX, (float)windowSizeY));
	background.setPosition(0.f, 0.f);
	background.setFillColor(sf::Color(50, 50, 50, 128));

	state.getGraphicEngine()->draw(background);

	sf::Text text;
	text.setFont(myFont);
	text.setFillColor(sf::Color::White);

	double ratioY = windowSizeY / 768.;
	text.setCharacterSize((int)(80 * ratioY));
	std::string string = "GAME OVER";
	text.setString(string);

	for (unsigned int i = 0; i < string.size(); i++)
	{
		text.setString(string.substr(0, i));
		if (text.getGlobalBounds().width >(float) windowSizeX)
		{
			string.insert(string.begin() + (i - 1), '\n');
			i = 0;
		}
	}
	text.setString(string);
	text.setPosition(sf::Vector2f(windowSizeX / 2.f - text.getGlobalBounds().width / 2., 
		windowSizeY / 2.f - text.getGlobalBounds().height / 2.));

	state.getGraphicEngine()->draw(text);
}