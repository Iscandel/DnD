#pragma once
#include "GameState.h"

#include "tools/Rng.h"
class SGameBeginningServer :
	public ServerGameState
{
public:
	SGameBeginningServer();
	~SGameBeginningServer();

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update();

	void init() override;

	bool catchEvent(const sf::Event& ev);

	virtual void processMessage(const Message& msg);

	bool isOnSamePos(int id, int x, int y) const;

	bool isValid(int x, int y);

	bool allSecretRoomValidated();

	void configureMaze();

protected:
	std::map<int, Point<int>> myChosenRoomById;
	Rng myRng;
};

