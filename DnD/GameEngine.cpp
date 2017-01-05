#include "GameEngine.h"

#include "GraphicEngine.h"


GameEngine::GameEngine()
:myIsFinished(false)
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
GameEngine::~GameEngine(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Traite un message issu de la file.
///////////////////////////////////////////////////////////////////////////////
void GameEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{		
	default:
		myGameStates.back()->processMessage(msg);
	break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Traite la file des messages, puis effectue l'ensemble des mises à jour à
// faire.
///////////////////////////////////////////////////////////////////////////////
void GameEngine::update()
{
	processQueue();
		
	for(unsigned int i = 0; i < myGameStates.size(); i++)
	{
		//Update if not paused
		if(!myGameStates[i]->isPaused())
			myGameStates[i]->update();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameEngine::initState(GameState::ptr state)
{
	state->linkGameEngine(this);
	state->linkGraphicEngine(getGraphicEngine());
	state->linkNetworkEngine(getNetworkEngine());
	state->linkSoundEngine(getSoundEngine());
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute un nouvel état de jeu par dessus le précédent (intérêt dans le cas
// d'un menu qui apparait en jeu. Le jeu est dessiné derrière, soit 2 états
// affichés, mais seul le premier capte les évènements
///////////////////////////////////////////////////////////////////////////////
void GameEngine::pushState(GameState::ptr state)
{
	initState(state);
	myGameStates.push_back(state);
	state->init();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool GameEngine::popState()
{
	if(myGameStates.size() != 0)
	{
		myGameStates.back()->free();
		myGameStates.pop_back();

		return true;
	}

	return false;
}

void GameEngine::catchEvents()
{
	sf::Event ev;
	while(getGraphicEngine()->getEvent(ev))
	{
		//Si évènement non géré par le moteur jeu, on l'envoie à l'état courant
		if(!handleEvent(ev))	
		{
			for(unsigned int i = myGameStates.size() - 1; i >= 0 ; i--)
			{
				if(myGameStates[i]->catchEvent(ev))
					break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameEngine::draw()
{
	for(unsigned int i = 0; i < myGameStates.size(); i++)
	{
		//Draw if not paused ?
		myGameStates[i]->draw();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GameEngine::setGameState(GameState::ptr g)
{
	//initState(g);
	while(popState());
	pushState(g);
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
		//if(ev.Key.Code == sf::Keyboard::F12)
		//	monEstDebug = !monEstDebug;
	}

	return handled;
}