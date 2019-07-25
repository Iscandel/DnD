#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

class SMainMenuSolo : public ClientGameState
{
public:
	SMainMenuSolo();
	~SMainMenuSolo();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	void onClic1P(gaia::MouseEvent& ev);

	void onClic2P(gaia::MouseEvent& ev);
};

