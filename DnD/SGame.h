#pragma once
#include "GameState.h"

#include <string>

class SGame : public ClientGameState
{
public:
	SGame();
	~SGame();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init();

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	std::string getTurnSound(int pos);

	void initDraggable(const std::string& imageId, const std::string& imageName, const std::string& widgetName);

protected:
	//std::vector<TimerFunction> myTimerFunctions;
	std::map<int, std::string> myTurnSoundByPlayerId;

protected:
	//Player* myStarter;
	//std::vector<Player*> myPlayers;
	//std::vector<Card> myCards;
};

