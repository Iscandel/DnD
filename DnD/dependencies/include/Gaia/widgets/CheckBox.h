#ifndef H__CHECKBOX_180820111315__H
#define H__CHECKBOX_180820111315__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/widgets/IText.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief CheckBox widget.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL CheckBox : public gaia::BaseWidget, public IText
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
	CheckBox(const std::string& name = "", 
			 int x = 0, 
			 int y = 0 , 
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
	CheckBox(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget is checked.
	///	
	/// \return true if it is checked, false if it is not checked.
	///////////////////////////////////////////////////////////////////////////
	bool isChecked() const {return myIsChecked;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Checks or unchecks the widget.
	///	
	/// \param checked : true to check it, false to unchecked.
	///////////////////////////////////////////////////////////////////////////
	void setChecked(bool checked);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the text position relatively to the box.
	///
	/// \param right : True to set the checkbox's text on the right, false to 
	/// set it on the left.
	///////////////////////////////////////////////////////////////////////////
	void setTextOnRight(bool right) {myIsTextOnRight = right;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the text is displayed on the right of the box.
	///
	/// \return right : True if the checkbox's text is displayed on the right, 
	/// false if it is on the left
	///////////////////////////////////////////////////////////////////////////
	bool isTextOnRight() const {return myIsTextOnRight;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the checkbox's text.
	///
	/// \param text : Text to set.
	///////////////////////////////////////////////////////////////////////////
	void setText(const std::string& text);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the text.
	///
	/// \return The text.
	///////////////////////////////////////////////////////////////////////////
	const std::string& getText() {return myText;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adjusts the widget width to fit the text width + the box width.
	///////////////////////////////////////////////////////////////////////////
	void adjustSize();

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///////////////////////////////////////////////////////////////////////////
	virtual void onWidgetEntered();

	///////////////////////////////////////////////////////////////////////////
	///\brief  This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onWidgetExited();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to a "state changed event" for this widget. State
	/// actually changes when the checkbox becomes checked or unchecked.
	///
	/// \param fucntion : Function to call when the event is triggered.
	/// \param instance : Object to which the function belongs. Let it to NULL
	/// or don't specify if you use a free function.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	//void subscribeStateChanged(void (Class::*fonction)(T), Instance instance)
	//{E_onTextChanged = bind1(fonction, instance);}
	void subscribeStateChanged(const GenericFunction& f)
	{E_onStateChanged = f;}

	void onStateChanged();

	//static const std::string myWidgetType;

protected:
	//@overide
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev);

protected:
	bool myIsChecked; ///< Is the checkBox checked ?
	bool myIsTextOnRight; ///< Is the text displayed on the right or on the left ?
	bool myIsStateChanging; ///<Prevents recursive calls on the state changing function

	GenericFunction E_onStateChanged;
	std::string myText; ///< Text.
};

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static CheckBox type
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(CheckBox)

} //end namespace

#endif