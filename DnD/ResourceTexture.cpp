#include "ResourceTexture.h"
#include "ResourcesFile.h"


ResourceTexture::ResourceTexture(void)
:myIsTransparentColor(false)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ResourceTexture::~ResourceTexture(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ResourceTexture::setTexturePath(const Color& transp, const std::string& path)
{
	myIsTransparentColor = true;
	myPath = path;
	myTransparentColor = transp;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ResourceTexture::setTexturePath(const std::string& path)
{
	myPath = path;
}

///////////////////////////////////////////////////////////////////////////
// Reloads the images
///////////////////////////////////////////////////////////////////////////
void ResourceTexture::reload(bool smooth)
{
	myLoadingStatus = IResource::IS_LOADING;

	long int size = 0;
	const bool freeMem = true;
	char* data = ResourcesFile::getInstance()->getFile(myPath, "TexturesDat", &size);

	myTexture.reload(data, size, freeMem, smooth);

	myLoadingStatus = IResource::IS_LOADED;
}

///////////////////////////////////////////////////////////////////////////
// Removes images from the resource, keeping alive offsets and transparency color
///////////////////////////////////////////////////////////////////////////
void ResourceTexture::free()
{
	myTexture.freeImage();

	//Specify that the resource is not loaded anymore
	myLoadingStatus = IResource::NOT_LOADED;
}