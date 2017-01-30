#ifndef H__LINKEDLABELS_110920112255__H
#define H__LINKEDLABELS_110920112255__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/Label.h"
#include "Gaia/widgets/GroupWidgets.h"
#include "Gaia/widgets/ISelectable.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Widget for labels which is part of a groupe, in which only one is
/// selected at a time.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL LinkedLabels : public Label, public ISelectable
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
	LinkedLabels(const std::string& name = "", 
				 int x = 0, 
				 int y = 0 , 
				 int width = 0, 
				 int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	LinkedLabels(const std::string& nom, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the text color when it is selected, and not selected.
	///
	/// \param selected : Selection color.
	/// \param normal : Normal color.
	///////////////////////////////////////////////////////////////////////////
	void setColors(const Color& selected, const Color& normal);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the widget is selected.
	///////////////////////////////////////////////////////////////////////////
	virtual void onSelected();

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the widget is unselected.
	///////////////////////////////////////////////////////////////////////////
	virtual void onUnselected();

	//Widget type
	//static const std::string myWidgetType;

protected:
	Color myNormalColor; ///< Normal text color.
	Color mySelectionColor; ///< Text color when selected

	//bool myIsSelected;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static LinkedLabels type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(LinkedLabels)

}; //end namespace

#endif