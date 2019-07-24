#include "GameEngine.h"

#include "GraphicEngine.h"


GameEngine::GameEngine()
:myIsFinished(false)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
GameEngine::~GameEngine(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{		
	default:
		if(myServerGameStates.size() > 0)
			myServerGameStates.back()->processMessage(msg);
		if (myClientGameStates.size() > 0)
			myClientGameStates.back()->processMessage(msg);
	break;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::update()
{
	processQueue();
		
	for (unsigned int i = 0; i < myServerGameStates.size(); i++)
	{
		//Update if not paused
		if (!myServerGameStates[i]->isPaused())
			myServerGameStates[i]->update();
	}

	for (unsigned int i = 0; i < myClientGameStates.size(); i++)
	{
		//Update if not paused
		if(!myClientGameStates[i]->isPaused())
			myClientGameStates[i]->update();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::initState(GameState::ptr state)
{
	state->linkGameEngine(this);
	state->linkGraphicEngine(getGraphicEngine());
	state->linkNetworkEngine(getNetworkEngine());
	state->linkSoundEngine(getSoundEngine());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::pushState(std::vector<GameState::ptr>& vector, GameState::ptr state)
{
	initState(state);
	vector.push_back(state);
	state->init();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GameEngine::popState(std::vector<GameState::ptr>& vector)
{
	if(vector.size() != 0)
	{
		vector.back()->free();
		vector.pop_back();

		return true;
	}

	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GameEngine::popState(std::vector<GameState::ptr>& vector, GameState::ptr state)
{
	std::vector<GameState::ptr>::iterator it = vector.erase(
		std::find(vector.begin(), vector.end(), state));

	return !(it == vector.end());

}
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::catchEvents()
{
	sf::Event ev;
	while(getGraphicEngine()->getEvent(ev))
	{
		//If ev not handled by the game engine, send to current state
		if(!handleEvent(ev))	
		{
			bool handled = false;
			for (int i = myServerGameStates.size() - 1; i >= 0; i--)
			{
				if (myServerGameStates[i]->catchEvent(ev)) {
					handled = true; break;
				}
			}

			if (handled)
				continue;

			for(int i = myClientGameStates.size() - 1; i >= 0 ; i--)
			{
				if(myClientGameStates[i]->catchEvent(ev))
					break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameEngine::draw()
{
	for(unsigned int i = 0; i < myClientGameStates.size(); i++)
	{
		//Draw if not paused ?
		myClientGameStates[i]->draw();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::setGameState(std::vector<GameState::ptr>& vector, GameState::ptr g)
{
	//initState(g);
	while(popState(vector));
	pushState(vector, g);
}

bool GameEngine::handleEvent(const sf::Event& ev)
{
	bool handled = false;

	if(ev.type == sf::Event::Closed)
	{
		stopGame();
		handled = true;
	}
	else if(ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Escape)
		{
			stopGame();
			handled = true;
		}
	}

	return handled;
}

void GameEngine::setClientGameState(GameState::ptr state)
{
	setGameState(myClientGameStates, state);
}

///////////////////////////////////////////////////////////////////////////
/// Adds a new state to the top of the game state stack of the game engine.
///
/// \param state The state to add.
///////////////////////////////////////////////////////////////////////////
void GameEngine::pushClientState(GameState::ptr state)
{
	pushState(myClientGameStates, state);
}

///////////////////////////////////////////////////////////////////////////
/// Removes the top state from the game state stack of the game engine.
///////////////////////////////////////////////////////////////////////////
bool GameEngine::popClientState()
{
	return popState(myClientGameStates);
}

///////////////////////////////////////////////////////////////////////////
/// Removes a given game state
///////////////////////////////////////////////////////////////////////////
bool GameEngine::popClientState(GameState::ptr state)
{
	return popState(myClientGameStates, state);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GameEngine::setServerGameState(GameState::ptr state)
{
	setGameState(myServerGameStates, state);
}


///////////////////////////////////////////////////////////////////////////
/// Adds a new state to the top of the game state stack of the game engine.
///
/// \param state The state to add.
///////////////////////////////////////////////////////////////////////////
void GameEngine::pushServerState(GameState::ptr state)
{
	pushState(myServerGameStates, state);
}

///////////////////////////////////////////////////////////////////////////
/// Removes the top state from the game state stack of the game engine.
///////////////////////////////////////////////////////////////////////////
bool GameEngine::popServerState()
{
	return popState(myServerGameStates);
}

///////////////////////////////////////////////////////////////////////////
/// Removes a given game state
///////////////////////////////////////////////////////////////////////////
bool GameEngine::popServerState(GameState::ptr state)
{
	return popState(myServerGameStates, state);
}