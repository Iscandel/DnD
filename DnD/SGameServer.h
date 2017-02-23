#pragma once

#include "GameState.h"

#include "Player.h"

class SGameServer : public ServerGameState
{
public:
	SGameServer();
	~SGameServer();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init() override;

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	//void sendMessage(const Message& msg);

	//void sendMessage(const Message& msg, int id);

	//void sendMessageExceptLocal(const Message& msg);

	//void sendMessageToAllExceptSome(const Message& msg, const std::vector<int>& excluded);

	void handlePlayerDefeat(Player::ptr player);


	void checkGameOver();

protected:
	//std::vector<TimerFunction> myTimerFunctions;
	bool nextPlayerIfHasLost(Player::ptr player);

protected:
	//Player* myStarter;
	//std::vector<Player*> myPlayers;
	//std::vector<Card> myCards;
};
