#ifndef H__SOUNDENGINE__H
#define H__SOUNDENGINE__H

#include "Engine.h"

#include <SFML/Audio.hpp>

#include "ResourceSoundBuffer.h"

class Sound
{
public:
	sf::Sound& getSound() { return mySound; }
	void setSoundBuffer(ResourceSoundBuffer::ptr buffer)
	{
		mySound.setBuffer(buffer->getBuffer());
		MyDummySoundBuffer = buffer;
	}

	sf::Sound::Status getStatus() const { return mySound.getStatus(); }
	void play() { mySound.play(); }
protected:
	ResourceSoundBuffer::ptr MyDummySoundBuffer;
	sf::Sound mySound;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Class handling the sound part.
///////////////////////////////////////////////////////////////////////////////
class SoundEngine : public Engine
{
public:
	typedef std::vector<Sound> SoundList;

public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///////////////////////////////////////////////////////////////////////////
	SoundEngine(void);

	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	~SoundEngine(void);

	///////////////////////////////////////////////////////////////////////////
	/// Processes a message.
	///
	/// \param msg The message to process.
	///////////////////////////////////////////////////////////////////////////
	virtual void processMessage(const Message& Msg);

	///////////////////////////////////////////////////////////////////////////
	/// Updates the sound engine. 
	///////////////////////////////////////////////////////////////////////////
	void update();

	void updateSounds();

	void playSound(const std::string& id);

	void pushSound(const std::string& id);

protected:
	bool myIsSoundEnabled;
	bool myIsMusicEnabled;

	SoundList mySounds;

	std::queue<Sound> myWaitingSounds;
};

#endif