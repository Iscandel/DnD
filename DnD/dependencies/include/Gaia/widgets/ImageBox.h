#ifndef H__IMAGEBOX_100920112202__H
#define H__IMAGEBOX_100920112202__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{

class GAIA_DLL ImageBox : public BaseWidget//, public IImage
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param x: X position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param y: Y position relatively to the parent widget (or the window if
	/// it is the top level widget).
	///
	/// \param width: Width of the widget.
	///
	/// \param height: Height of the widget.
	///////////////////////////////////////////////////////////////////////////
	ImageBox(const std::string& name = "", 
				int x = 0, 
				int y = 0, 
				int width = 0, 
				int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	ImageBox(const std::string& name, const IntRect& dimensions);

	void setImage(const Image& image);

	Image& getImage() {return monImage;}


	//Widget type
	//static const std::string myWidgetType;

protected:
	Image monImage;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static ImageBox type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(ImageBox)

} //end namespace

#endif