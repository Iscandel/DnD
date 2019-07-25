#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

class SConnectionMenu :
	public ClientGameState
{
public:
	SConnectionMenu();
	~SConnectionMenu();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	void onClicConnection(gaia::MouseEvent& ev);

	void onClicHost(gaia::MouseEvent& ev);
};

