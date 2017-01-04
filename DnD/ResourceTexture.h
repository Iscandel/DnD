#ifndef H__RESOURCETEXTURE_180120141738__H
#define H__RESOURCETEXTURE_180120141738__H

#include "IResource.h"
#include "DataTexture.h"
#include "tools/Point.h"
#include "tools/Rectangle.h"

#include <iostream>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Ressource traduisant un ensemble d'images
///////////////////////////////////////////////////////////////////////////////

class ResourceTexture : public IResource
{
public:
	ResourceTexture(/*PtrImage Img*/);
	~ResourceTexture(void);

	///////////////////////////////////////////////////////////////////////////
	// Renvoie un pointeur sur l'image numéro num
	///////////////////////////////////////////////////////////////////////////
	PtrTexture getTexture() {return myTexture.getTexture();}

	///////////////////////////////////////////////////////////////////////////
	// Ajoute une image (Cas multi images)
	// Params : transp -> Couleur de transparence
	//			offset -> L'offset d'affichage
	//			offset2-> L'offset miroir
	//			img	   -> L'image
	///////////////////////////////////////////////////////////////////////////
	void setTexturePath(const Color& transp, const std::string& path);

	///////////////////////////////////////////////////////////////////////////
	//Ajoute une image standard (cas où la ressource image ne contient qu'une image)
	///////////////////////////////////////////////////////////////////////////
	void setTexturePath(const std::string& path);

	///////////////////////////////////////////////////////////////////////////
	// Recharge le set d'images à l'aide du vecteur d'images passé en paramètre
	// Si smooth vaut true, on applique le smoothing aux images
	///////////////////////////////////////////////////////////////////////////
	virtual void reload(bool smooth = false);

	///////////////////////////////////////////////////////////////////////////
	// Supprime les images de la ressource, mais conserve les offsets et la 
	// couleur de transparence
	///////////////////////////////////////////////////////////////////////////
	virtual void free();

protected:
	//int id; //ok ?
	DataTexture<PtrTexture> myTexture;
	std::string myPath;
	bool myIsTransparentColor;
	Color myTransparentColor;
};

typedef std::shared_ptr<ResourceTexture> PtrResourceTexture;

#endif