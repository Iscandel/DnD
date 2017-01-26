#pragma once

#include "View.h"

#include "Maze.h"
#include <SFML/Graphics.hpp>

class GameView :
	public View
{
public:
	GameView(const std::string& path);
	~GameView(void);

	virtual void draw(GameState& state);
	void loadViewPosition(const std::string& path);

protected:
	void drawRect(GameState& state, const sf::Color& col, const sf::Vector2f& pos, const sf::Vector2f& size);
	void drawCellShadows(GameState& state, double x, double y, int windowSizeX, int windowSizeY);
	void drawImage(GameState& state, std::vector<Image>& resource, const sf::Vector2f& pixelSize, const sf::Vector2f& pos, float rotation);
	void drawSecretRoom(GameState& state, int x, int y, int windowsSizeX, int windowSizeY, const sf::Color& fill);
};

