#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

#include <SFML/Audio.hpp>

class SMainMenu :
	public ClientGameState
{
public:
	SMainMenu();
	~SMainMenu();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	void onClicSolo(gaia::MouseEvent& ev);

	void onClicMulti(gaia::MouseEvent& ev);
};

