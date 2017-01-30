#ifndef H__BASELISTBOXITEM_230820111443__H
#define H__BASELISTBOXITEM_230820111443__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/BaseGraphics.h"

namespace gaia
{
class ListBox;

///////////////////////////////////////////////////////////////////////////////
/// \brief Base class for ListBox item.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL BaseListBoxItem : public BaseWidget
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
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
	BaseListBoxItem(const std::string& name = "", 
					int x = 0, 
					int y = 0, 
					int width = 0, 
					int height = 0);

	//template<class T>
	//virtual void drawItem(T* widget, BaseGraphics* Gfx, int x = 0, int y = 0) = 0;
	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws this item.
	///
	/// \param widget : The ListBox owning the item.
	///
	/// \param selected : Indicates whether the item is in a selected state or not.
	///
	/// \param Gfx : Pointer the graphic engine.
	///
	/// \param x : Top left X position of the item, relatively to the ListBox 
	/// coordinate system.
	///
	/// \param y : Top left Y position of the item, relatively to the ListBox 
	/// coordinate system.
	///////////////////////////////////////////////////////////////////////////
	virtual void drawItem(ListBox* widget,
						  bool selected, 
						  BaseGraphics* Gfx, 
						  int x = 0, 
						  int y = 0) = 0;

	virtual std::string getValue() {return "";}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indi
	///
	/// \param widget : The ListBox owning the item.
	///
	/// \param selected : Indicates whether the item is in a selected state or not.
	///
	/// \param Gfx : Pointer the graphic engine.
	///
	/// \param x : Top left X position of the item, relatively to the ListBox 
	/// coordinate system.
	///
	/// \param y : Top left Y position of the item, relatively to the ListBox 
	/// coordinate system.
	///////////////////////////////////////////////////////////////////////////
	//bool isSelected() const {return myIsSelected;}
	//virtual void setSelectionner(bool sel) {myIsSelected = sel;}

	//@override
	//virtual bool handleMousePressed(MouseEvent& ev)
	//{
	//	setSelectionner(!isSelected());

	//	return BaseWidget::handleMousePressed(ev);
	//}

	//virtual T getValue() = 0;
	//template<class T>
	//virtual void getValue(T& val);

//protected:
//	bool myIsSelected;
};

GAIA_REGISTER_TYPE(BaseListBoxItem)

} //end namespace

#endif