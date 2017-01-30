#ifndef H__XMLGUILOADER__H
#define H__XMLGUILOADER__H

#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/XMLLoader/XMLConfig.h"
#include "Gaia/Rectangle.h"
#include "Gaia/LayoutInfos.h"
#include "Gaia/tools/NonCopyable.h"
#include "Gaia/widgets/TypedefList.h"

#include <string>

class TiXmlElement;

namespace gaia
{
namespace xml
{
///////////////////////////////////////////////////////////////////////////////
// Renvoie un rectangle de nouvelles dimensions relativement à la taille de la 
// fenêtre. Les dimensions de base sont données pour du 640*480
///////////////////////////////////////////////////////////////////////////////
//IntRect redimensionner(float x, float y, float largeur, float hauteur);

//void GAIA_XML_DLL resizeAbsolute(PtrWidget widget, PtrWidget parent, int x, int y, int width, int height, bool keepRelative);
//
//void GAIA_XML_DLL resizeRelative(PtrWidget widget, double x, double y, double width, double height);

bool GAIA_XML_DLL handleWidget(TiXmlElement* widgetNode, bool reload = false, PtrWidget parent = PtrWidget());
void GAIA_XML_DLL handleProperty(PtrWidget widget, const std::string& key, TiXmlElement* element);
bool GAIA_XML_DLL handleDimensions(PtrWidget widget, PtrWidget parent, TiXmlElement* element);
LayoutInfos GAIA_XML_DLL constructLayoutInfos2(TiXmlElement* widgetPosAttributes);

class GAIA_XML_DLL XMLGuiLoader : public NonCopyable
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	XMLGuiLoader(void);

	///////////////////////////////////////////////////////////////////////////
	// \brief Destructor.
	///////////////////////////////////////////////////////////////////////////
	~XMLGuiLoader(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Loads the layout using the given path to the XML file.
	///
	/// \param path :path to the file
	///
	/// \param reload :true if you only want to reload widget and not create
	/// them. Reloading concerns some parameters like look&feel, dimensions...
	///////////////////////////////////////////////////////////////////////////
	static bool loadGUI(const std::string& path, bool reload = false);

protected:
	///////////////////////////////////////////////////////////////////////////
	// Charge les widgets enfants du widget de manière récursive
	// parent : le widget considéré
	// element : La position du curseur dans l'arbre xml
	///////////////////////////////////////////////////////////////////////////
	//static void getWidgetsEnfants(PtrWidget parent, TiXmlElement* element);

	///////////////////////////////////////////////////////////////////////////
	// Parse la chaine position et l'affecte au widget
	///////////////////////////////////////////////////////////////////////////
	//static void setWidgetPosition(PtrWidget widget, const std::string& position);

	///////////////////////////////////////////////////////////////////////////
	// Gestion d'erreur
	///////////////////////////////////////////////////////////////////////////
	//static void erreurParser(const std::string& fichier, int ligne);
};

} //end namespace xml

} //end namespace

#endif