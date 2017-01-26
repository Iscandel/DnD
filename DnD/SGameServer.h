#pragma once

#include "GameState.h"

#include "Player.h"

class SGameServer : public ServerGameState
{
public:
	SGameServer();
	~SGameServer();

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

	void init() override;

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	void sendMessage(const Message& msg);

	void sendMessage(const Message& msg, int id);

	void sendMessageExceptLocal(const Message& msg);

	void sendMessageToAllExceptSome(const Message& msg, const std::vector<int>& excluded);

	void handlePlayerDefeat(Player::ptr player);

protected:
	//std::vector<TimerFunction> myTimerFunctions;
	bool nextPlayerIfHasLost(Player::ptr player);

protected:
	//Player* myStarter;
	//std::vector<Player*> myPlayers;
	//std::vector<Card> myCards;
};
