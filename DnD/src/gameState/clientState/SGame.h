#pragma once
#include "gameState/GameState.h"

#include "Gaia/Gaia.h"

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

	void playSoundAndLockMove(const std::string& idSound);
	void pushSoundAndLockMove(const std::string& idSound);

protected:
	void onSendChatMessage(gaia::KeyboardEvent& ev);

	void unlockMove() { myMoveIsLocked = false; }

protected:
	//std::vector<TimerFunction> myTimerFunctions;
	std::map<int, std::string> myTurnSoundByPlayerId;

	bool myMoveIsLocked;
};

