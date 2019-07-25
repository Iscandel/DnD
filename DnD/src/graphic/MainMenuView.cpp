#include "MainMenuView.h"

#include "gameState/GameState.h"
#include "game/GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"

MainMenuView::MainMenuView()
{
}


MainMenuView::~MainMenuView()
{
}

void MainMenuView::loadViewPosition(const std::string& path)
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

void MainMenuView::draw(GameState& state)
{
	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	sf::RectangleShape background(sf::Vector2f((float)windowSizeX, (float)windowSizeY));
	background.setPosition(0.f, 0.f);
	background.setFillColor(sf::Color(0, 0, 0));

	state.getGraphicEngine()->draw(background);

	sf::Text text;
	text.setFont(myFont);
	text.setFillColor(sf::Color::White);

	double ratioY = windowSizeY / 768.;
	text.setCharacterSize((int)(90 * ratioY));
	std::string string = "DnD";
	text.setFillColor(sf::Color::White);
	text.setString(string);
	text.setPosition(windowSizeX / 2.f - text.getGlobalBounds().width / 2.f, 0.);

	state.getGraphicEngine()->draw(text);
}