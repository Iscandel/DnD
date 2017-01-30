#pragma once
#include "View.h"
class GameWonView :
	public View
{
public:
	GameWonView(const std::string& path);
	~GameWonView();

	void draw(GameState& state) override;
	void loadViewPosition(const std::string& path);
};

