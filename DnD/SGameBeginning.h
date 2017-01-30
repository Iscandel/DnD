#pragma once
#include "GameState.h"
class SGameBeginning :
	public ClientGameState
{
public:
	SGameBeginning();
	~SGameBeginning();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);
};

