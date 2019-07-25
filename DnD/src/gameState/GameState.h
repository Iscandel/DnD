#ifndef H__GAMESTATE_150820130049_H
#define H__GAMESTATE_150820130049_H

#include "game/Engine.h"
#include "game/Message.h"

#include "tools/WithSmartPtr.h"
#include "graphic/View.h"

#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////////////
/// \brief Base class for game state.
///////////////////////////////////////////////////////////////////////////////
class GameState : public Engine, public WithSmartPtr<GameState>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///////////////////////////////////////////////////////////////////////////
	GameState();
	//GameState(int NomEtat) : monNomEtat(NomEtat) {}

	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	virtual ~GameState(void);

	///////////////////////////////////////////////////////////////////////////
	/// Initializes the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void init() {};

	///////////////////////////////////////////////////////////////////////////
	/// Frees the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void free() {};

	///////////////////////////////////////////////////////////////////////////
	/// Pauses the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void pause() { myIsPaused = true; }

	///////////////////////////////////////////////////////////////////////////
	/// Resumes the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void resume() { myIsPaused = false; }

	///////////////////////////////////////////////////////////////////////////
	/// Updates the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void update() = 0;
	
	///////////////////////////////////////////////////////////////////////////
	/// Catches the game events
	///////////////////////////////////////////////////////////////////////////
	virtual bool catchEvent(const sf::Event& ev) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// Draws the game state.
	///////////////////////////////////////////////////////////////////////////
	virtual void draw();

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the state is paused or not.
	///
	/// \return true if the state is currently paused, false otherwise.
	///////////////////////////////////////////////////////////////////////////
	bool isPaused() const {return myIsPaused;}

	///////////////////////////////////////////////////////////////////////////
	/// Sets a new state to the (owning) game engine.
	///
	/// \param state The new state to set.
	///////////////////////////////////////////////////////////////////////////
	void setClientGameState(GameState::ptr state);
	void pushClientGameState(GameState::ptr state);

	void setServerGameState(GameState::ptr state);
	void pushServerGameState(GameState::ptr state);

	bool isVisible() const {return myIsVisible;}

	void setVisible(bool visible) {myIsVisible = visible;}

	void setView(View::ptr view) {myView = view;}

	virtual void sendMessage(const Message& m, int id = 0) = 0;

	//bool isNotLocalId(int id);

protected:
	bool myIsPaused;
	bool myIsVisible;

	View::ptr myView;
};

class ClientGameState : public GameState
{
public:
	virtual void sendMessage(const Message& m, int id = 0) override;
};

class ServerGameState : public GameState
{
public:
	void sendMessageTo(const Message& m, int id);
	//Id not used here
	virtual void sendMessage(const Message& m, int id = 0) override;

	void sendMessageToAllExcept(const Message& msg, int id);

	void sendMessageExceptLocal(const Message& msg);

	void sendMessageToAllExceptSome(const Message& msg, const std::vector<int>& excluded);
};

#endif