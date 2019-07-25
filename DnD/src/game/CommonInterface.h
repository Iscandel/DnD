#ifndef H__COMMONINTERFACE__H
#define H__COMMONINTERFACE__H

#include "GameEngine.h"
#include "network/NetworkEngine.h"
#include "sound/SoundEngine.h"
#include "graphic/GraphicEngine.h"

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