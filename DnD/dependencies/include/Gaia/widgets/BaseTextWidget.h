#ifndef H__BASETEXTWIDGET__29082011118_H
#define H__BASETEXTWIDGET__29082011118_H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/widgets/IText.h"
#include "Gaia/widgets/ICaret.h"
#include "Gaia/tools/Observer.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Base class for widgets dealing with text, like TextBox and TextField.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL BaseTextWidget :
	public gaia::BaseWidget, public IText, public ICaret, public Observable
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
	BaseTextWidget(const std::string& name = "", 
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
	BaseTextWidget(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	//virtual void setFocus(bool b);
	//@override
	//virtual void onLostFocus();

	///////////////////////////////////////////////////////////////////////////
	// Héritée. Met à jour
	///////////////////////////////////////////////////////////////////////////
	//virtual void update(unsigned int elapsedTime);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes text.
	///
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param endingPos : Text index defining the ending of the suppression.
	///////////////////////////////////////////////////////////////////////////
	virtual void deleteTextRange(unsigned int startingPos, unsigned int endingPos) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes text.
	///
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param amount : Amount of characters to deletes.
	///////////////////////////////////////////////////////////////////////////
	virtual void deleteText(unsigned int startingPos, unsigned int amount) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a section of text, from startingPos to endingPos, and
	/// replaces it by the given string
	///
	/// \param text : Text to insert in replacement.
	/// \param startingPos : Text index defining the begining of the suppression.
	/// \param endingPos : Text index defining the ending of the suppression.
	///////////////////////////////////////////////////////////////////////////
	virtual void replaceTextRange(const std::string& text, unsigned int startingPos, unsigned int endingPos) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a section of text, from startingPos, and replaces it by
	/// the given string.
	///
	/// \param text : Text to insert in replacement.
	/// \param startingPos : Text index defining the begining of the replacement.
	/// \param amount : Text index defining the ending of the replacement.
	///////////////////////////////////////////////////////////////////////////
	virtual void replaceText(const std::string& text, unsigned int startingPos, unsigned int amount) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Inserts the given string at the given position. Position must be 
	/// a valid one.
	///
	/// \param text : Text to insert.
	/// \param pos : Position of insertion.
	///////////////////////////////////////////////////////////////////////////
	virtual void insertText(const std::string& text, unsigned int pos) = 0;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the whole text.
	///
	/// \param text : Text to set.
	///////////////////////////////////////////////////////////////////////////
	virtual void setText(const std::string& text) {myText = text;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the whole plain text.
	///
	/// \return The text.
	///////////////////////////////////////////////////////////////////////////
	const std::string& getText() const {return myText;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Assigns a new position to the caret.
	///
	/// \param pos : Position to set.
	///////////////////////////////////////////////////////////////////////////
	void setCaretPosition(unsigned int pos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Moves the last selection value according to the given quantity.
	/// 
	/// If the position is not correct, nothing is done.
	///
	/// \param amount : Amount of move.
	///////////////////////////////////////////////////////////////////////////
	void moveSelection(unsigned int amount);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Called when a changement occured in the text. If the user
	/// subscribed to this event, the function he gave is called.
	///////////////////////////////////////////////////////////////////////////
	void onTextChanged();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the current selected text.
	///
	/// \return The selected text.
	///////////////////////////////////////////////////////////////////////////
	std::string getSelectedText();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the widget in a read-only mode. User can move the caret
	/// through the text, and scroll if it is handled, but he cannot modify
	/// the text by either way.
	///
	/// \param readOnly : True to set the read-only mode, false to set the 
	/// normal mode.
	///////////////////////////////////////////////////////////////////////////
	void setReadOnly(bool readOnly) {myIsReadOnly = readOnly;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget is in a read-only mode.
	///
	/// \return True if it is in a read-only mode, false if it is in a normal 
	/// mode.
	///////////////////////////////////////////////////////////////////////////
	bool isReadOnly() const {return myIsReadOnly;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to a "text changed event" for this widget.
	///
	/// \param fucntion : Function to call when the event is triggered.
	/// \param instance : Object to which the function belongs. Let it to NULL
	/// or don't specify if you use a free function.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	//void subscribeTextChanged(void (Class::*fonction)(T), Instance instance)
	//{E_onTextChanged = bind1(fonction, instance);}
	void subscribeTextChanged(const GenericFunction& f)
	{E_onTextChanged = f;}

	//Widget type
	//static const std::string myWidgetType;
	
protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual bool handleMousePressed_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseHover_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a Keyboard event.
	///////////////////////////////////////////////////////////////////////////
	virtual bool handleKeyPressed_impl(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a Keyboard event.
	///////////////////////////////////////////////////////////////////////////
	virtual bool handleTextEntered_impl(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles text suppression.
	///
	/// \param posIfNotSelected : If the text is not selected, it is used to
	/// define the position of suppression.
	///////////////////////////////////////////////////////////////////////////
	void handleDeleting(unsigned int posIfNotSelected);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adjusts the caret if it exceeds the text lenght (e.g. during a 
	/// suppression)
	///////////////////////////////////////////////////////////////////////////
	void adjustCaret();

protected:
	std::string myText; ///< Full text.
	bool myIsDragging; ///< 
	GenericFunction E_onTextChanged;
	Point myMousePos; ///< To recall the mouse position
	bool myIsReadOnly; ///< Read only mode
};

GAIA_REGISTER_TYPE(BaseTextWidget)

}

#endif
