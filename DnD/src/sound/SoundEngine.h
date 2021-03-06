#ifndef H__SOUNDENGINE__H
#define H__SOUNDENGINE__H

#include "game/Engine.h"

#include <SFML/Audio.hpp>

#include "resources/ResourceSoundBuffer.h"

class Sound
{
public:
	sf::Sound& getSound() { return mySound; }
	void setSoundBuffer(ResourceSoundBuffer::ptr buffer)
	{
		mySound.setBuffer(buffer->getBuffer());
		MyDummySoundBuffer = buffer;
	}

	void setCallback(std::function<void()> callback) { myCallback = callback; }

	sf::Sound::Status getStatus() const { return mySound.getStatus(); }
	void play() { mySound.play(); }

	void callback() { if (myCallback) myCallback(); }
protected:
	ResourceSoundBuffer::ptr MyDummySoundBuffer;
	sf::Sound mySound;
	std::function<void()> myCallback;
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

	void playSound(const std::string& id, std::function<void()> callback);

	void pushSound(const std::string& id);

	void pushSound(const std::string& id, std::function<void()> callback);

	void playMusic(const std::string& path);

protected:
	bool myIsSoundEnabled;
	bool myIsMusicEnabled;

	SoundList mySounds;

	std::queue<Sound> myWaitingSounds;

	sf::Music myMusic;
};

#endif