#pragma once
#include "GameState.h"

#include <string>

class SGame : public ClientGameState
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

	std::string getTurnSound(int pos);

protected:
	//std::vector<TimerFunction> myTimerFunctions;
	std::vector<std::string> myTurnSoundByPlayerVectorPos;

protected:
	//Player* myStarter;
	//std::vector<Player*> myPlayers;
	//std::vector<Card> myCards;
};

