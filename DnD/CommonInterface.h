#ifndef H__COMMONINTERFACE__H
#define H__COMMONINTERFACE__H

#include "GameEngine.h"
#include "NetworkEngine.h"
#include "SoundEngine.h"
#include "GraphicEngine.h"

class CommonInterface
{
public:
	CommonInterface(void);
	~CommonInterface(void);

	void run();

protected:
	GameEngine myGame;
	NetworkEngine myNetwork;
	SoundEngine mySound;
	GraphicEngine myGraphic;
};

#endif