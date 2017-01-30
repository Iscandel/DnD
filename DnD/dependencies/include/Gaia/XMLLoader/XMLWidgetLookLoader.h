#ifndef H__XMLWIDGETLOOKLOADER_22062011_H
#define H__XMLWIDGETLOOKLOADER_22062011_H

#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/XMLLoader/XMLConfig.h"
#include "Gaia/ImageSheetsManager.h"
#include "Gaia/WidgetLookManager.h"

#include <string>

class TiXmlElement;
namespace gaia
{
namespace xml
{
///////////////////////////////////////////////////////////////////////////////
/// \brief XML loader of widget looks.
///////////////////////////////////////////////////////////////////////////////
class GAIA_XML_DLL XMLWidgetLookLoader
{
public:
	XMLWidgetLookLoader(void);
	~XMLWidgetLookLoader(void);

	static bool loadImageSet(const std::string& imageSetName);
	static bool loadLooks(const std::string& pathToLooks);
	
	static bool load(const std::string& imageSetPath, const std::string& LookPath);

protected:
	//static void getWidgetsEnfants(const std::string nomEnfant, /*int numEnfant,*/ ThemeWidget& theme, TiXmlElement* element);

	static bool handleSheet(TiXmlElement* sheetNode);

	static bool handleAreaLook(WidgetLook& theme, 
						  TiXmlElement* widgetAttributes, 
						  const std::string& childName, 
						  bool isChild);

	static void handleImageLook(WidgetLook& theme, 
						 TiXmlElement* widgetAttributes, 
						 const std::string& widgetName, 
						 bool isChild);

	static bool handleChildLook(WidgetLook& theme, TiXmlElement* widgetAttributes, bool isChild);

	static LayoutInfos constructLayoutInfos(
							 TiXmlElement* widgetAttributes);

	static void handleChildDimensions(WidgetLook& theme, 
							 TiXmlElement* widgetAttributes,
							 const std::string& childName, 
							 bool isChild);

	static void handleChildPosition(WidgetLook& theme, 
							 TiXmlElement* widgetAttributes,
							 const std::string& childName, 
							 bool isChild);

	static void handleChildWidth(WidgetLook& theme, 
							 TiXmlElement* widgetAttributes,
							 const std::string& childName, 
							 bool isChild);

	static void handleChildHeight(WidgetLook& theme, 
							 TiXmlElement* widgetAttributes,
							 const std::string& childName, 
							 bool isChild);

	static void handleRenderer(WidgetLook& theme, TiXmlElement* widgetAttributes, bool isChild);

	static bool handleWidgetLook(TiXmlElement* widgetNode);

	static bool handleCommon(WidgetLook &theme, 
							 TiXmlElement* widgetAttributes, 
							  const std::string& key,
							 const std::string& widgetName, 
							 bool isChild);
};

} //end namespace xml

} //end namespace

#endif
