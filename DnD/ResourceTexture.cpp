#include "ResourceTexture.h"
#include "ResourcesFile.h"


ResourceTexture::ResourceTexture(void)
:myIsTransparentColor(false)
{
}


ResourceTexture::~ResourceTexture(void)
{
}

	void ResourceTexture::setTexturePath(const Color& transp, const std::string& path)
	{
		myIsTransparentColor = true;
		myPath = path;
		myTransparentColor = transp;
	}

	///////////////////////////////////////////////////////////////////////////
	//Ajoute une image standard (cas où la ressource image ne contient qu'une image)
	///////////////////////////////////////////////////////////////////////////
	void ResourceTexture::setTexturePath(const std::string& path)
	{
		myPath = path;
	}

	///////////////////////////////////////////////////////////////////////////
	// Recharge le set d'images à l'aide du vecteur d'images passé en paramètre
	// Si smooth vaut true, on applique le smoothing aux images
	///////////////////////////////////////////////////////////////////////////
	void ResourceTexture::reload(bool smooth)
	{
		myLoadingStatus = IResource::IS_LOADING;

		long int size = 0;
		const bool freeMem = true;
		char* data = ResourcesFile::getInstance()->getFile(myPath,"TexturesDat", &size);

		myTexture.reload(data, size, freeMem, smooth);

		myLoadingStatus = IResource::IS_LOADED;
	}

	///////////////////////////////////////////////////////////////////////////
	// Supprime les images de la ressource, mais conserve les offsets et la 
	// couleur de transparence
	///////////////////////////////////////////////////////////////////////////
	void ResourceTexture::free()
	{
		myTexture.freeImage();
	
		//On indique que la ressource n'est plus chargée
		myLoadingStatus = IResource::NOT_LOADED;
	}