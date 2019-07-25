#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"

class SLobbyServer :
	public ServerGameState
{
public:
	SLobbyServer();
	~SLobbyServer();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	void onClicStart(gaia::MouseEvent& ev);
};

