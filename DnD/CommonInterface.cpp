#include "CommonInterface.h"

#include "Tools/Logger.h"

#include "SGame.h"

//#include <iostream>

CommonInterface::CommonInterface(void)
{
	//utiles::creerGuiDat();

	myGame.linkGameEngine(&myGame);
	myGame.linkGraphicEngine(&myGraphic);
	myGame.linkNetworkEngine(&myNetwork);
	myGame.linkSoundEngine(&mySound);

	myNetwork.linkGameEngine(&myGame);
	myNetwork.linkGraphicEngine(&myGraphic);
	myNetwork.linkSoundEngine(&mySound);

	mySound.linkGameEngine(&myGame);
	mySound.linkGraphicEngine(&myGraphic);
	mySound.linkNetworkEngine(&myNetwork);

	myGraphic.linkGameEngine(&myGame);
	myGraphic.linkNetworkEngine(&myNetwork);
	myGraphic.linkSoundEngine(&mySound);

	//MessageSender::getInstance()->linkGameEngine(&myGame);
}


CommonInterface::~CommonInterface(void)
{
}


void CommonInterface::run()
{
	try
	{
		GameState::ptr sgame(new SGame);
		myGame.setGameState(sgame);//lobby);

		while(!myGame.isFinished())
		{
			myGame.catchEvents();

			myGame.update();
			mySound.update();
			myNetwork.update();
			myGraphic.update();

			myGraphic.draw();
		}
	}
	catch(const std::exception& e)
	{
		ILogger::log(ILogger::ERRORS) << e.what() << "\n";
		getchar();
	}
	catch(...)
	{
		ILogger::log(ILogger::ERRORS) << "Unknown exception...\n";
		getchar();
	}
}