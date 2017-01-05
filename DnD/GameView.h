#pragma once

#include "View.h"

class GameView :
	public View
{
public:
	GameView(const std::string& path);
	~GameView(void);

	virtual void draw(GameState& state);
	void loadViewPosition(const std::string& path);
};

