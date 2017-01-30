#pragma once
#include "GameState.h"
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
};

