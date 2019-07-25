#pragma once
#include "View.h"

class GameLostView :
	public View
{
public:
	GameLostView();
	~GameLostView();

	void draw(GameState& state) override;
};

