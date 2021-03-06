#pragma once
#include "gameState/GameState.h"

class SGameWon :
	public ClientGameState
{
public:
	SGameWon(bool won);
	~SGameWon();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	std::string getTurnSound(int pos);

protected:
	bool myIsWon;
};

