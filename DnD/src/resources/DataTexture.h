#ifndef H__DATAIMAGE__H
#define H__DATAIMAGE__H

//#include "tools/Position.h"
//#include "IRessource.h"
//#include "GraphiqueUtiles.h"
#include "tools/Color.h"
#include <SFML\Graphics.hpp>
#include <memory>
//#include "gui/SFMLTexture.h"

//GraphiqueHelper::getInstance()::PtrImage; /typedef...ex : typedef boost::shared_ptr<sf::Image> PtrImage
//Graphique = new sfmlGraphique(), Graphique = new openGLGraphique()

typedef std::shared_ptr<sf::Texture> PtrTexture;

///////////////////////////////////////////////////////////////////////////////
// Classe conteneur de base des images, ainsi que leurs offset associ�s
///////////////////////////////////////////////////////////////////////////////
template<class T>
class DataTexture
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Constructeur par d�faut
	///////////////////////////////////////////////////////////////////////////
	DataTexture(void);

	///////////////////////////////////////////////////////////////////////////
	// Params : MonImg -> L'image
	//			offset -> l'offset
	//			offset2-> l'offset miroir pour les directions sup�rieures � bas
	//			smooth -> Indique si il faut appliquer le smoothing � l'image
	///////////////////////////////////////////////////////////////////////////
	//DataImage(T /*PtrImage*/ tex, const Position<float>& offset, const Position<float>& offset2, bool smooth = false);

	///////////////////////////////////////////////////////////////////////////
	// Params : MonImg -> L'image
	//			transp -> Rend la couleur transparente sur l'image
	//			offset -> l'offset
	//			offset2-> l'offset miroir pour les directions sup�rieures � bas
	//			smooth -> Indique si il faut appliquer le smoothing � l'image
	///////////////////////////////////////////////////////////////////////////
	//DataImage(T tex, const Color& transp, const Position& offset, const Position& offset2,  bool smooth = false);

	///////////////////////////////////////////////////////////////////////////
	// Params : offset -> l'offset
	//			offset2-> l'offset miroir pour les directions sup�rieures � bas
	///////////////////////////////////////////////////////////////////////////
	//DataImage(const Position<float>& offset, const Position<float>& offset2);

	///////////////////////////////////////////////////////////////////////////
	// Params : transp -> Rend la couleur transparente sur l'image
	//			offset -> l'offset
	//			offset2-> l'offset miroir pour les directions sup�rieures � bas
	///////////////////////////////////////////////////////////////////////////
	//DataImage(const Color& transp, const Position<float>& offset, const Position<float>& offset2);
	
	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	~DataTexture(void);

	///////////////////////////////////////////////////////////////////////////
	// Renvoie un pointeur sur l'image
	///////////////////////////////////////////////////////////////////////////
	T /*PtrImage*/ getTexture() {return myTexture;}

	///////////////////////////////////////////////////////////////////////////
	// Accesseurs sur les offsets (normal et miroir) associ�s � l'image
	///////////////////////////////////////////////////////////////////////////
	//const Position& getOffset() const {return MonOffset;}
	//const Position& getOffset2() const {return MonOffset2;}

	//void setOffset(const Position& c) {MonOffset = c;}
	//void setOffset2(const Position& c) {MonOffset2 = c;}

	///////////////////////////////////////////////////////////////////////////
	/// Deletes the image
	///////////////////////////////////////////////////////////////////////////
	void freeImage();

	///////////////////////////////////////////////////////////////////////////
	/// Reloads the texture with the given one and smooths it if the smooth
	/// parameter is true.
	///
	/// \param tex The texture to load.
	/// \param smooth true to smooth the texture, false otherwise.
	///////////////////////////////////////////////////////////////////////////
	void reload(T /*PtrImage*/ MonImg, bool smooth = false);

	void reload(char* data, long int size, bool freeMem, bool smooth = false);
protected:
	//Offset normal
	//Position myOffset;
	//Offset miroir
	//Position myOffset2;
	///texture pointer
	T /*PtrImage*/ myTexture;
	//La couleur de transparence, le cas �ch�ant
	Color myTranparentColor;
	//Indique si la couleur de transparence est utilis�e
	bool myIsTransparence;

	float myRotation;
};


///////////////////////////////////////////////////////////////////////////////
template<class T>
DataTexture<T>::DataTexture(void)
{
}

///////////////////////////////////////////////////////////////////////////////
//template<class T>
//DataImage<T>::DataImage(const Color& transp, const Position<float>& offset, const Position<float>& offset2)
//:myIsTransparence(true)
//,MyOffset(offset)
//,MyOffset2(offset2)
//,myTranparentColor(transp)
//{
//}

///////////////////////////////////////////////////////////////////////////////
//template<class T>
//DataImage<T>::DataImage(T /*PtrImage*/ tex, const Position<float>& offset, const Position<float>& offset2,  bool smooth)
//:myIsTransparence(false)
//,MyOffset(offset)
//,MyOffset2(offset2)
//,myTexture(tex)
//{
//	//MonImage->SetSmooth(smooth);
//}

///////////////////////////////////////////////////////////////////////////////
// Deuxi�me constructeur
///////////////////////////////////////////////////////////////////////////////
//template<class T>
//inline DataImage<jpgui::PtrSFMLTexture>::DataImage(T tex, 
//												   const Position<float>& offset, 
//												   const Position<float>& offset2,  
//												   bool smooth)
//:myIsTransparence(false)
//,MyOffset(offset)
//,MyOffset2(offset2)
//,myTexture(tex)
//{
//	MonImage->getSFMLImage().SetSmooth(smooth);
//}

///////////////////////////////////////////////////////////////////////////////
// 3�me constructeur
///////////////////////////////////////////////////////////////////////////////
//template<class T>
//DataTexture<T>::DataTexture(const Position<float>& offset, const Position<float>& offset2)
//:myIsTransparence(false)
//,MyOffset(offset)
//,MyOffset2(offset2)
//{
//}

///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
template<class T>
DataTexture<T>::~DataTexture(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// D�truit l'image
///////////////////////////////////////////////////////////////////////////////
template<class T>
void DataTexture<T>::freeImage()
{
	//r�initialisation du pointeur intelligent 
	//(-> appel � delete si use_count == 1) (should not happen if it comes from
	//a resource manager)
	myTexture.reset();
}

///////////////////////////////////////////////////////////////////////////////
// Recharge l'image avec l'image pass�e en param�tre
///////////////////////////////////////////////////////////////////////////////
template<class T>
void DataTexture<T>::reload(T /*PtrImage*/ tex, bool smooth)
{
	//static int cpt = 0;
	//cpt++;
	//std::cout << cpt << std::endl;
	myTexture = tex;

	//Si on a besoin de mettre de la transparence pour une couleur
	if(myIsTransparent)
		myTexture->CreateMaskFromColor(MaCouleurTransparence);

	myTexture->SetSmooth(smooth);
}

template<class T>
void DataTexture<T>::reload(char* data, long int size, bool freeMem, bool smooth = false)
{
	myTexture.reset(new sf::Texture);
	myTexture->loadFromMemory(data, size);

	if(smooth)
	{
		myTexture->setSmooth(smooth);
	}

	if(freeMem)
		delete data;
}



///////////////////////////////////////////////////////////////////////////////
// Recharge l'image avec l'image pass�e en param�tre
///////////////////////////////////////////////////////////////////////////////
//template<>
//inline void DataImage<jpgui::PtrSFMLTexture>::reload(jpgui::PtrSFMLTexture MonImg, bool smooth)
//{
//	////static int cpt = 0;
//	////cpt++;
//	////std::cout << cpt << std::endl;
//	//MonImage = MonImg;
//
//	//Si on a besoin de mettre de la transparence pour une couleur
//	if(myIsTransparence)
//		myTexture->getSFMLImage().CreateMaskFromColor(MaCouleurTransparence);
//
//	myTexture->getSFMLImage().SetSmooth(smooth);
//}

//typedef DataImage<::PtrImage> DataImageJeu;

#endif