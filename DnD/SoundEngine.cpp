#include "SoundEngine.h"

SoundEngine::SoundEngine(void)
{
}

SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{
	default:
		break;
	}
}

void SoundEngine::update()
{
	processQueue();
}