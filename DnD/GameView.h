#pragma once

#include "BaseGameView.h"

#include "Entity.h"
#include "Maze.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

class GameView :
	public BaseGameView
{
public:
	GameView(const std::string& path);
	~GameView(void);

	virtual void draw(GameState& state);
	void loadViewPosition(const std::string& path);

protected:
	void drawPlayer(GameState& state, Player::ptr player, int windowSizeX, int windowSizeY);
	sf::Color getSecretRoomColorById(int id);
};

