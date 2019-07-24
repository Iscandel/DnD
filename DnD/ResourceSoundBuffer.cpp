#include "ResourceSoundBuffer.h"



ResourceSoundBuffer::ResourceSoundBuffer(PtrSoundBuffer buffer)
:mySoundBuffer(buffer)
{
	myLoadingStatus = IResource::IS_LOADED;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ResourceSoundBuffer::~ResourceSoundBuffer(void)
{
}

