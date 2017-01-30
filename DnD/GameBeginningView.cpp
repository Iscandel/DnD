#include "GameBeginningView.h"

#include "GameState.h"
//#include "Game.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"
//
//
#include "ResourceImageManager.h"


GameBeginningView::GameBeginningView(const std::string& path)
:BaseGameView(path)
{
}


GameBeginningView::~GameBeginningView()
{
}

void GameBeginningView::draw(GameState& state)
{
	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	static bool set = false;
	if (!set)
	{
		initializeSecretRoomColor(state);
		set = true;
	}

	Game& game = state.getGameEngine()->getGame();
	Maze::ptr maze = game.getMaze();

	const Point<double>& playerName = getGivenPosition("playerName");

	//Black background
	drawRect(state, sf::Color::Black, sf::Vector2f(), sf::Vector2f(windowSizeX, windowSizeY));

	//Grey board
	drawRect(state, sf::Color(128, 128, 128), sf::Vector2f(), sf::Vector2f(0.60359375f * windowSizeX, windowSizeY));

	drawMaze(state, maze, windowSizeX, windowSizeY);

	auto players = game.getManager().getPlayers();
	for (Player::ptr player : players)
	{
		if (player)
		{
			const Point<int>& secretRoom = player->getSecretRoomPos();
			drawSecretRoom(state, secretRoom.x, secretRoom.y, windowSizeX, windowSizeY, mySecretRoomColorById[player->getId()]);
		}	
	}

	auto entity = game.getEntity(game.getCurrentIdTurn());
	if (entity)
		drawPlayerName(state, entity, playerName.x, playerName.y, windowSizeX, windowSizeY);
	else
	{
		drawPlayerName(state, "Other:", false, playerName.x, playerName.y, windowSizeX, windowSizeY);
	}
}