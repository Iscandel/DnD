#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"

class SLobby :
	public ClientGameState
{
public:
	SLobby();
	~SLobby();

	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	void onSendChatMessage(gaia::KeyboardEvent& ev);
};

