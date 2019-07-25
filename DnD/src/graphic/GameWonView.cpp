#include "GameWonView.h"

#include "gameState/GameState.h"
//#include "Game.h"
#include "resources/TextureManager.h"
#include "game/GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"

GameWonView::GameWonView(const std::string& path)
{
	loadViewPosition(path);
}


GameWonView::~GameWonView()
{
}

void GameWonView::loadViewPosition(const std::string& path)
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

void GameWonView::draw(GameState& state)
{
	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	Point<double>& textPos = getGivenPosition("text");

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
	text.setCharacterSize((int) (80 * ratioY));
	std::string string = game.getWinner()->getName() + " won !\n Press any key to return to main menu.";
	text.setString(string);

	for (unsigned int i = 0; i < string.size(); i++)
	{
		text.setString(string.substr(0, i));
		if (text.getGlobalBounds().width > (float) windowSizeX)
		{
			string.insert(string.begin() + (i - 1), '\n');
			i = 0;
		}
	}
	text.setString(string);
	text.setPosition(sf::Vector2f(textPos.x * windowSizeX, textPos.y * windowSizeY));

	state.getGraphicEngine()->draw(text);
}