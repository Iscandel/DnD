#include "ResourceImage.h"
#include "TextureManager.h"

///////////////////////////////////////////////////////////////////////////////
// Constructeur
///////////////////////////////////////////////////////////////////////////////
ResourceImage::ResourceImage()
{
	myLoadingStatus = IResource::NOT_LOADED;
}

///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
ResourceImage::~ResourceImage(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute une image (Cas multi images)
// Params : transp -> Couleur de transparence
//			offset -> L'offset d'affichage
//			offset2-> L'offset miroir
//			img	   -> L'image
// 
// NB : C'est au manager de fournir l'image. Peu importe si il récupère le chemin
// dans RessourceImage ou dataImage ou sur lui. Le manager sait quel dat utiliser
// pour charger l'image.
///////////////////////////////////////////////////////////////////////////////
//void BasiqueResourceImage::add(const Color& transp, 
//							 const Position<int>& offset,
//							 const Position<int>& offset2,
//							 PtrImage img)
//{
//	//Ajout de la DataImage
//	MyImages.push_back(DataImage<PtrImage>(transp, offset, offset2));
//
//	//Si l'image est présente, on l'ajoute aussi
//	if(img != NULL)
//	{
//		//On n'indique pas que la ressource est chargée, il peut y avoir
//		//d'autres images
//		MyImages.back().reload(img);
//	}	
//
//	//On rappelle que la ressource n'est pas chargée
//	myLoadingStatus = IResource::NOT_LOADED;
//}

Image::Image(int textureId, const IntRect& rect, const Point<int>& offset)
:myTextureId(textureId)
,myRect(rect)
,myOffset(offset)
{
}

void Image::reload()
{
	myTexture = TextureManager::getInstance()->getResource(myTextureId);
	if (myRect.width == -1 || myRect.height == -1)
	{
		myRect.x = 0;
		myRect.y = 0;
		myRect.width = myTexture->getTexture()->getSize().x;
		myRect.height = myTexture->getTexture()->getSize().y;
	}
}

void Image::free()
{
	myTexture.reset();
}

///////////////////////////////////////////////////////////////////////////////
// Cas image unique
///////////////////////////////////////////////////////////////////////////////
void ResourceImage::add(const Image& im)
{
	myImages.push_back(im);
}

///////////////////////////////////////////////////////////////////////////////
// Libération des images sans toucher aux offsets / couleur de transparence
///////////////////////////////////////////////////////////////////////////////
void ResourceImage::free()
{
	for(unsigned int i = 0; i < myImages.size(); i++)
	{
		myImages[i].free();
	}

	//On indique que la ressource n'est plus chargée
	myLoadingStatus = IResource::NOT_LOADED;
}

///////////////////////////////////////////////////////////////////////////////
// Recharge les images à l'aide du vecteur d'images passé en paramètre et 
// applique le smoothing si le booléen smooth vaut true
///////////////////////////////////////////////////////////////////////////////
void ResourceImage::reload()
{
	myLoadingStatus = IResource::IS_LOADING;

	//On recharge toutes les images
	for(unsigned int i = 0; i < myImages.size(); i++)
	{
		myImages[i].reload();
	}

	//On indique que la ressource est chargée
	myLoadingStatus = IResource::IS_LOADED;
}