#ifndef H_GAMEENGINE_150820130029_H
#define H_GAMEENGINE_150820130029_H

#include <vector>

#include "Engine.h"
#include "Message.h"
#include "GameState.h"
//#include "Game.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Class handling the game.
///////////////////////////////////////////////////////////////////////////////
class GameEngine : public Engine
{
public:
	
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///////////////////////////////////////////////////////////////////////////
	GameEngine();

	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	~GameEngine(void);
	
	///////////////////////////////////////////////////////////////////////////
	/// Processes a message.
	///
	/// \param msg The message to process.
	///////////////////////////////////////////////////////////////////////////
	virtual void processMessage(const Message& msg);

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game engine. Processes the message queue and updates the
	/// game states.
	///////////////////////////////////////////////////////////////////////////
	void update();

	///////////////////////////////////////////////////////////////////////////
	/// Initializes the given game state.
	///
	/// \param state The state to initialize.
	///////////////////////////////////////////////////////////////////////////
	void initState(GameState::ptr state);

	///////////////////////////////////////////////////////////////////////////
	/// Applies the given game state to the game engine.
	///
	/// \param state The state to set.
	///////////////////////////////////////////////////////////////////////////
	void setGameState(GameState::ptr state);

	///////////////////////////////////////////////////////////////////////////
	/// Adds a new state to the top of the game state stack of the game engine.
	///
	/// \param state The state to add.
	///////////////////////////////////////////////////////////////////////////
	void pushState(GameState::ptr state);

	///////////////////////////////////////////////////////////////////////////
	/// Removes the top state from the game state stack of the game engine.
	///////////////////////////////////////////////////////////////////////////
	bool popState();

	void catchEvents();

	///////////////////////////////////////////////////////////////////////////
	/// Performs the drawing.
	///////////////////////////////////////////////////////////////////////////
	void draw();

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the game is finished.
	///
	/// \return true if the game is finished, false if it is not finished.
	///////////////////////////////////////////////////////////////////////////
	bool isFinished() {return myIsFinished;}

	//Game& getGame() {return myGame;}

	//GameServer& getGameServer() {return myGameServer;}

	bool handleEvent(const sf::Event& ev);

	void stopGame() {myIsFinished = true;}

protected:

	bool myIsFinished;
	std::vector<GameState::ptr> myGameStates; //< Vector of game states
	//Game myGame;
	//GameServer myGameServer;
};

#endif