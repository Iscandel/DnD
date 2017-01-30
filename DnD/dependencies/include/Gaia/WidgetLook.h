#ifndef H__WIDGETLOOK_060620112134__H
#define H__WIDGETLOOK_060620112134__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Rectangle.h"
#include "Gaia/widgets/BaseWidget.h"

#include <map>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Struct grouping a sheet name and an image name.
///////////////////////////////////////////////////////////////////////////////
struct GAIA_DLL SheetImage
{
	///////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor.
	///////////////////////////////////////////////////////////////////////////
	SheetImage() {}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param imageSheet : widget to which the look is set.
	///////////////////////////////////////////////////////////////////////////
	SheetImage(const std::string& imageSheet, 
				 const std::string& imageName)
	:sheet(imageSheet)
	,imageName(imageName)
	{
	}

	std::string sheet; ///< Sheet name.
	std::string imageName; ///< Image name
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Describes the look of a given widget.
///
/// It associates the correct widget renderer to the widget and initializes it
/// with correct rendering parameters.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL WidgetLook
{
public:
	typedef std::map<std::string, SheetImage> ImageByState; 
	typedef std::map<std::string, LayoutInfos> LayoutAreaByName;
	typedef std::map<std::string, Rect<double> > AreaByName;

public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	WidgetLook(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Destructor.
	///////////////////////////////////////////////////////////////////////////
	//~WidgetLook(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Initializes a child look.
	///
	/// \param widgetName : Parent name.
	///////////////////////////////////////////////////////////////////////////
	//void initChildren(const std::string& widgetName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the widget look.
	///
	/// \param widget : widget to which the look is set.
	///////////////////////////////////////////////////////////////////////////
	void initWidget(PtrWidget widget);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the widget renderer name.
	///
	/// \param rendererName : the name to set.
	///////////////////////////////////////////////////////////////////////////
	void setWidgetRenderer(const std::string& rendererName) {myRenderer = rendererName;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds an image that will be drawn by the renderer.
	///
	/// \param stateName : State defining the image, to identify when it it drawn.
	/// \param imageSheetName : The name of image sheet containing this image.
	/// \param imageName : Image name.
	///////////////////////////////////////////////////////////////////////////
	void addImage(const std::string& stateName, 
				  const std::string& imageSheetName, 
				  const std::string& imageName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new area.
	///
	/// \param areaName : Name to give to this area.
	/// \param rect : Rectangle defining the area (with relative coords : 
	/// 0.0 to 1.0)
	///////////////////////////////////////////////////////////////////////////
	void addLayoutArea(const std::string& areaName, const LayoutInfos& infos);
	//void addArea(const std::string& areaName, const Rect<double>& rect);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a child widget name.
	///
	/// All functions relative to this child look must be called before
	/// adding a new child by calling this function again !
	///
	/// \param name : Child name.
	/// \param type : Widget type.
	///////////////////////////////////////////////////////////////////////////
	void addChild(const std::string& name, const std::string& type);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a child widget renderer name.
	///
	/// \param rendereName : Name of the renderer to set to the last child.
	///////////////////////////////////////////////////////////////////////////
	void addChildWidgetRenderer(const std::string& rendererName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a child widget image.
	///
	/// \param childName : The name of the targeted child.
	/// \param stateName : State name of the image.
	/// \param imageSheetName : Name of the image sheet.
	/// \param imageName : Image name.
	///////////////////////////////////////////////////////////////////////////
	void addChildImage(const std::string& childName, 
					   const std::string& stateName, 
					   const std::string& imageSheetName, 
					   const std::string& imageName);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a child widget renderer name.
	///
	/// \param childName : The name of the targeted child.
	/// \param areaName : Name to give to this area.
	/// \param rect : Area.
	///////////////////////////////////////////////////////////////////////////
	void addChildLayoutArea(const std::string& childName, 
					  const std::string& areaName, 
					  const LayoutInfos& infos);
					 // const Rect<double>& rect);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a child widget relative position (top left corner + size).
	///
	/// \param name :  The name of the targeted child.
	/// \param pos : The relative position (top left corner + size with values
	/// from 0.0 to 1.0)
	///////////////////////////////////////////////////////////////////////////
	//void addChildDimensions(const std::string& name, const Rect<double>& pos);

	void addChildLayout(const std::string& name, const LayoutInfos& infos);

	void setChildPosLayout(const std::string& name, const std::string& value);
	void setChildWidhtLayout(const std::string& name, const std::string& value);
	void setChildHeightLayout(const std::string& name, const std::string& value);

	PtrLayoutInfos getCloneLayoutInfos(const std::string& name);

protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Initializes the given widget with rendering informations.
	///
	/// \param w :  The targeted widget.
	/// \param widgetRenderer : Name of the widget renderer.
	/// \param images : Image list for the renderer.
	/// \param areas : Area list for the renderer.
	///////////////////////////////////////////////////////////////////////////
	void init(PtrWidget w, 
			  const std::string& widgetRenderer, 
			  const ImageByState& images, 
			  const LayoutAreaByName& areas);

protected:
	ImageByState myImages;
	LayoutAreaByName myLayoutAreas;
	//AreaByName myAreas;
	std::string myRenderer;

	std::vector<std::string> myChildNames;
	std::vector<std::string> myChildTypes;
	std::vector<std::string> myChildWidgetRenderer;
	std::map<std::string, ImageByState> myChildImages;
	//std::map<std::string, AreaByName> myChildAreas;
	std::map<std::string, LayoutAreaByName> myChildLayoutAreas;
	//std::map<std::string, Rect<double> > myChildPositions;
	std::map<std::string, LayoutInfos> myChildPositions;
};

};

#endif