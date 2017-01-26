#pragma once
#include "IResource.h"

#include "tools/WithSmartPtr.h"
#include <memory>

#include <SFML/Audio.hpp>

typedef std::shared_ptr<sf::SoundBuffer> PtrSoundBuffer;

class ResourceSoundBuffer :
	public IResource, public WithSmartPtr<ResourceSoundBuffer>
{
public:
	ResourceSoundBuffer(PtrSoundBuffer);
	~ResourceSoundBuffer();

	sf::SoundBuffer& getBuffer() { return *mySoundBuffer; }

protected:
	PtrSoundBuffer mySoundBuffer;
};

