#include "SoundEngine.h"

#include "SoundBufferManager.h"

#include "tools/Logger.h"

SoundEngine::SoundEngine(void)
:myIsSoundEnabled(true)
,myIsMusicEnabled(false)
{
}

SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{
	case Message::MessageType::PLAY_MUSIC:
	{
		//playMusic((TypeMusique)Msg.iDonnees[Message::cle::jouerMusique::TYPE]);
	}
	break;

	case Message::MessageType::STOP_MUSIC:
	{
		//stopMusic();
	}
	break;

	case Message::MessageType::PLAY_SOUND:
	{
		playSound(msg.sData[Message::Key::PlaySound::ID_SOUND]);
	}
	break;

	default:
		break;
	}
}

void SoundEngine::update()
{
	processQueue();

	updateSounds();
}

void SoundEngine::updateSounds()
{
	bool erased = false;
	SoundList::iterator it = mySounds.begin();
	for (; it != mySounds.end();)
	{
		if (it->getStatus() == sf::Sound::Stopped)
		{
			erased = true;
			it->callback();
			it = mySounds.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (mySounds.size() == 0 && myWaitingSounds.size() != 0)
	{
		mySounds.push_back(myWaitingSounds.front());
		myWaitingSounds.pop();
		mySounds.back().play();
	}

	//if(erased)
	//	SoundBufferManager::getInstance()->freeResources();
}

void SoundEngine::playMusic(const std::string& path)
{
	if (myMusic.openFromFile(path))
	{
		myMusic.play();
	}
	else
	{
		ILogger::log() << "Music " << path << " cannot be loaded.\n";
	}
}

void SoundEngine::playSound(const std::string& id)
{
	if (!myIsSoundEnabled)
		return;

	mySounds.push_back(Sound());

	ResourceSoundBuffer::ptr Ressource = SoundBufferManager::getInstance()->getResource(id);

	mySounds.back().setSoundBuffer(Ressource);
	mySounds.back().play();
}

void SoundEngine::playSound(const std::string& id, std::function<void()> callback)
{
	if (!myIsSoundEnabled)
		return;

	mySounds.push_back(Sound());

	ResourceSoundBuffer::ptr Ressource = SoundBufferManager::getInstance()->getResource(id);

	mySounds.back().setSoundBuffer(Ressource);
	mySounds.back().setCallback(callback);
	mySounds.back().play();
}

void SoundEngine::pushSound(const std::string& id)
{
	if (!myIsSoundEnabled)
		return;

	Sound sound;

	ResourceSoundBuffer::ptr Ressource = SoundBufferManager::getInstance()->getResource(id);

	sound.setSoundBuffer(Ressource);

	myWaitingSounds.push(sound);
}

void SoundEngine::pushSound(const std::string& id, std::function<void()> callback)
{
	if (!myIsSoundEnabled)
		return;

	Sound sound;

	ResourceSoundBuffer::ptr Ressource = SoundBufferManager::getInstance()->getResource(id);

	sound.setSoundBuffer(Ressource);
	sound.setCallback(callback);

	myWaitingSounds.push(sound);
}