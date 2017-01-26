#include "SoundBufferManager.h"

#include "tools/Logger.h"
#include "ResourcesFile.h"


SoundBufferManager::SoundBufferManager()
{
}


SoundBufferManager::~SoundBufferManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// H�rit�e. Libere toutes les ressources qui sont uniquement utilis�es par 
// le manager
///////////////////////////////////////////////////////////////////////////////
void SoundBufferManager::freeResources()
{
	MapResources::iterator it = myResources.begin();
	for (; it != myResources.end();)
	{
		if (it->second.unique())
		{
			it = myResources.erase(it);
		}
		else
		{
			++it;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// H�rit�e. Lib�re la ressource id si seul le manager l'utilise
///////////////////////////////////////////////////////////////////////////////
void SoundBufferManager::freeResource(std::string id)
{
	MapResources::iterator it = myResources.find(id);
	if (it == myResources.end())
		throw std::runtime_error("SoundBuffer " + id + " should already exist.\n");

	if (it->second.unique())
	{
		myResources.erase(id);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Lib�re la ressource id si seul le manager l'utilise
///////////////////////////////////////////////////////////////////////////////
SoundBufferManager::PtrResource SoundBufferManager::loadResource(std::string id)
{
	long int size = 0;
	PtrSoundBuffer buffer(new sf::SoundBuffer);

	char* cBuffer = ResourcesFile::getInstance()->getFile(id, "SoundDat", &size);
	if (!buffer->loadFromMemory(cBuffer, size))
	{
		ILogger::log(ILogger::ERRORS) << "File \"" << id << "\" not found\n";
	}

	delete[] cBuffer;

	ResourceSoundBuffer::ptr Resource(new ResourceSoundBuffer(buffer));
	myResources.insert(std::make_pair(id, Resource));

	return myResources[id];
}