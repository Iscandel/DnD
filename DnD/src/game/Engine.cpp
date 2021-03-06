#include "Engine.h"
#include "GameEngine.h"
#include "network/NetworkEngine.h"
#include "graphic/GraphicEngine.h"
#include "sound/SoundEngine.h"

Engine::Engine()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Engine::~Engine()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::sendMessageToGraphic(const Message& m)
{
	myGraphics->addMessage(m);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::sendMessageToSound(const Message& m)
{
	mySound->addMessage(m);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::sendMessageToNetwork(const Message& m)
{
	myNetwork->addMessage(m);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::sendMessageToGame(const Message& m)
{
	myGame->addMessage(m);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::addMessage(const Message& msg)
{	
	std::lock_guard<std::mutex> lock(myMutexQueue);
	myMessageQueue.push(msg);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Engine::processQueue()
{
	std::queue<Message> fileCopy;

	//Copie des �l�ments de la file dans une seconde file, en une seule
	//op�ration, afin d'�viter que la file des messages se re-remplissent
	//� cause de l'acc�s par le thread r�seau, durant le traitement des
	//op�rations
	{
		std::lock_guard<std::mutex> lock(myMutexQueue);
		while( !myMessageQueue.empty())
		{
			fileCopy.push(myMessageQueue.front());
			myMessageQueue.pop();
		}
	}

	//Traitement des messages
	while(!fileCopy.empty())
	{
		processMessage(fileCopy.front());
		fileCopy.pop();
	}
}

