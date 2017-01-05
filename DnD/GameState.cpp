#include "GameState.h"
#include "GameEngine.h"
#include "NetworkEngine.h"

//#include "Game.h"

GameState::GameState()
:myIsPaused(false)
,myIsVisible(true)
{
	init();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
GameState::~GameState(void)
{
	free();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameState::setGameState(GameState::ptr state)
{
	getGameEngine()->setGameState(state);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameState::sendMessage(const Message& m)
{
	if(getNetworkEngine()->isMulti())// && !getNetworkEngine()->isServer())
	{
		getNetworkEngine()->sendMessage(m);
	}
	else
	{
		getGameEngine()->processMessage(m); //send to server first
	}
			
}

//bool GameState::isNotLocalId(int id) 
//{
//	Game& game = getGameEngine()->getGame();
//	const GameServer& server = game.getServerData();
//	return server.isNotLocalId(id);
//	//if(id != game.getPlayerId())
//	//	return true;
//
//	//return false;
//}

void GameState::draw()
{
	if(myView)
		myView->draw(*this);
}


