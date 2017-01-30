#pragma once
#include "GameState.h"

class SGameWon :
	public ClientGameState
{
public:
	SGameWon();
	~SGameWon();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	std::string getTurnSound(int pos);
};

