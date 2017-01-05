#pragma once
#include "GameState.h"

class SGame : public GameState
{
public:
	SGame();
	~SGame();

	///////////////////////////////////////////////////////////////////////////
	/// Pauses the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void pause() {}

	///////////////////////////////////////////////////////////////////////////
	/// Resumes the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void resume() {}

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

protected:
	//std::vector<TimerFunction> myTimerFunctions;

protected:
	//Player* myStarter;
	//std::vector<Player*> myPlayers;
	//std::vector<Card> myCards;
};

