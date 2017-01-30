#pragma once
#include "View.h"
class MainMenuView :
	public View
{
public:
	MainMenuView();
	~MainMenuView();

	void loadViewPosition(const std::string& path);

	void draw(GameState& state);
};

