#pragma once
#include "resources/ResourcesManager.h"

#include "resources/ResourceSoundBuffer.h"

class SoundBufferManager :
	public ResourcesManager<ResourceSoundBuffer, std::string, SoundBufferManager>
{
public:
	SoundBufferManager();
	~SoundBufferManager();

	///////////////////////////////////////////////////////////////////////////
	/// Frees all current used resources if they are ONLY used by the Manager.
	///////////////////////////////////////////////////////////////////////////
	virtual void freeResources() override;

	///////////////////////////////////////////////////////////////////////////
	/// Frees the desired resources if it is ONLY used by the Manager (not used
	/// in the game for example).
	///
	/// \param id Identifier of the desired resource.
	///////////////////////////////////////////////////////////////////////////
	virtual void freeResource(std::string id) override;

	protected:
	///////////////////////////////////////////////////////////////////////////
	/// Loads the desired resource.
	///
	/// \param id Identifer of the desired resource.
	///
	/// \return A pointer to the resource.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrResource loadResource(std::string id) override;
};