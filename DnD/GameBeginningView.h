#pragma once
#include "BaseGameView.h"
class GameBeginningView :
	public BaseGameView
{
public:
	GameBeginningView(const std::string& path);
	~GameBeginningView();

	virtual void draw(GameState& state);
};

