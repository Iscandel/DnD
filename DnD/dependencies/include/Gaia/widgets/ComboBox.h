#ifndef H__COMBOBOX_240920111726__H
#define H__COMBOBOX_240920111726__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/widgets/TypedefList.h"
#include "Gaia/widgets/ListBox.h"

namespace gaia
{
class TextListBoxItem;

///////////////////////////////////////////////////////////////////////////////
/// \brief ListBox extension to fit to the ComboBox class.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ComboListBox : public ListBox//<TextListBoxItem>
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
	ComboListBox(const std::string& name = "", int x = 0, int y = 0, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	ComboListBox(const std::string& name, const IntRect& dimensions);

	//Widget type
	//static const std::string myWidgetType;

protected:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Updates the item list.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMousePressed_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Updates the item list.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Updates the item list.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseHover_impl(MouseEvent& ev);

protected:
	int myClickCounter; ///< Tools to determine when we should hide the ListBox.
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static ComboListBox type.
///////////////////////////////////////////////////////////////////////////////
//GAIA_REGISTER_TYPE(ComboListBox)
GAIA_REGISTER_FULL_TYPE(ComboListBox, ListBox)


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Box enabling to select a value among a list which can be showed or
/// hidden.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ComboBox : public gaia::BaseWidget, public IText
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
	ComboBox(const std::string& name = "", 
			 int x = 0, 
			 int y = 0, 
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
	ComboBox(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the internal TextBox.
	///
	/// \return A smart pointer to the TextBox.
	///////////////////////////////////////////////////////////////////////////
	PtrTextBox getTextBox();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the internal ListBox.
	///
	/// \return A smart pointer to the ListBox.
	///////////////////////////////////////////////////////////////////////////
	PtrComboListBox getListBox();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the internal Button.
	///
	/// \return A smart pointer to the Button.
	///////////////////////////////////////////////////////////////////////////
	PtrButton getButton();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new item to the ComboBox. An item is a string.
	///
	/// \param item : String to add.
	///////////////////////////////////////////////////////////////////////////
	void addItem(const std::string& item);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the maximum number of elements displayed, before needing
	/// to scroll using the vertical scrollbar.
	///
	/// \param number : Maximum number of elements displayed at a time.
	///////////////////////////////////////////////////////////////////////////
	void setNumberElementsDisplayed(unsigned int number);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the maximum number of elements displayed, before needing
	/// to scroll using the vertical scrollbar.
	///
	/// \return The number of elements displayed at a time.
	///////////////////////////////////////////////////////////////////////////
	unsigned int getNumberElementsDisplayed() const {return myNumberElementsDisplayed;}

	const std::string PREFIX_TEXTBOX;  ///< Generic TextBox name
	const std::string PREFIX_LISTBOX;  ///< Generic ListBox name
	const std::string PREFIX_BUTTON;   ///< Generic Button name
	//const std::string SUFFIX;

	///Widget type
	//static const std::string myWidgetType;

protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when clicking on the button.
	///
	/// \param ev : Mouse event triggered.
	///////////////////////////////////////////////////////////////////////////
	void onClicCombo(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when the selection was made in the list.
	///
	/// \param ev : Mouse event triggered.
	///////////////////////////////////////////////////////////////////////////
	void onNewSelection(Event& ev);

protected:
	unsigned int myNumberElementsDisplayed; ///< Number of elements displayed at a time

};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static ComboBox type
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(ComboBox)

} //end namespace

#endif