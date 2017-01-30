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
void GameState::setClientGameState(GameState::ptr state)
{
	getGameEngine()->setClientGameState(state);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameState::pushClientGameState(GameState::ptr state)
{
	getGameEngine()->pushClientState(state);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameState::setServerGameState(GameState::ptr state)
{
	getGameEngine()->setServerGameState(state);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameState::pushServerGameState(GameState::ptr state)
{
	getGameEngine()->pushServerState(state);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ClientGameState::sendMessage(const Message& m, int id)
{
	if(getNetworkEngine()->isMulti() && !getNetworkEngine()->isServer())
	{
		getNetworkEngine()->sendMessage(m);
	}
	else
	{
		Message mod = m;
		mod.iData[0] = id;
		getGameEngine()->processMessage(mod); //send to server first
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


void ServerGameState::sendMessage(const Message& msg, int id)
{
	getGameEngine()->processMessage(msg);
	//	getNetworkEngine()->sendMessageTCPToAll(msg);
}

void ServerGameState::sendMessageToAllExcept(const Message& msg, int id)
{
	//	getNetworkEngine()->sendMessageTCPToAllExcept(msg, id);
}

void ServerGameState::sendMessageExceptLocal(const Message& msg)
{
	//	getNetworkEngine()->sendMessageTCPToAll(msg);
}

void ServerGameState::sendMessageToAllExceptSome(const Message& msg, const std::vector<int>& excluded)
{
	Game& game = getGameEngine()->getGame();
	bool notLocal = false;

	for (int excl : excluded)
	{
		//		if (game.isLocalId(excl))
		notLocal = true;
	}

	if (!notLocal)
		getGameEngine()->processMessage(msg);

	//	getNetworkEngine()->sendMessageTCPToAllExcept(msg, excluded)
}