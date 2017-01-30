#pragma once
#include "View.h"

#include "Entity.h"
#include "Maze.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

class BaseGameView :
	public View
{
public:
	BaseGameView(const std::string& path);
	~BaseGameView();

	void loadViewPosition(const std::string& path);

protected:
	void drawRect(GameState& state, const sf::Color& col, const sf::Vector2f& pos, const sf::Vector2f& size);
	void drawCellShadows(GameState& state, double x, double y, int windowSizeX, int windowSizeY);
	void drawImage(GameState& state, std::vector<Image>& resource, const sf::Vector2f& pixelSize, const sf::Vector2f& pos, float rotation);
	void drawSecretRoom(GameState& state, int x, int y, int windowsSizeX, int windowSizeY, const sf::Color& fill);
	void drawPlayerName(GameState& state, const std::string& str, bool localId, float x, float y, int windowSizeX, int windowSizeY);
	void drawPlayerName(GameState& state, Entity::ptr player, float x, float y, int windowSizeX, int windowSizeY);
	void drawLivesAndSteps(GameState& state, Player::ptr player, float x, float y, int windowSizeX, int windowSizeY);
	void drawMaze(GameState& state, Maze::ptr maze, int windowSizeX, int windowSizeY);
	void initializeSecretRoomColor(GameState& state);

protected:
	static std::map<int, sf::Color> mySecretRoomColorById;
};

