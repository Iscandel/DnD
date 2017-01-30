#pragma once
#include "Gaia/widgets/ImageBox.h"

class DraggableImage :
	public gaia::ImageBox
{
public:
	DraggableImage(const std::string& name = "",
		int x = 0,
		int y = 0,
		int width = 0,
		int height = 0);
	~DraggableImage();

protected:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMousePressed_impl(gaia::MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(gaia::MouseEvent& ev);

	//////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseHover_impl(gaia::MouseEvent& ev);

	gaia::Point convertToScreenCoordinates(const gaia::Point& pos);

protected:
	bool myIsDragging;
	gaia::Point myOffset;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static ImageBox type.
///////////////////////////////////////////////////////////////////////////////
namespace gaia {
	GAIA_REGISTER_FULL_TYPE(DraggableImage, ImageBox)
}