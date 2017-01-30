#ifndef H__WINDOW_281020112346__H
#define H__WINDOW_281020112346__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/widgets/TypedefList.h"

namespace gaia
{
	class WindowImageRenderer;
class GAIA_DLL TitleBar : public gaia::BaseWidget
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
	TitleBar(const std::string& name = "", 
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
	TitleBar(const std::string& name, const IntRect& dimensions);

		///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse pressed event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMousePressed_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse released event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse move event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseHover_impl(MouseEvent& ev);

	PtrButton getCloseButton();

	//PtrButton getMinimizeButton();

protected:
	const std::string PREFIX_CLOSEBUTTON;
	Point myMousePos;
	bool myIsResizing;
};

GAIA_REGISTER_TYPE(TitleBar)

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL Window : public gaia::BaseWidget
{
public:
	struct PrivResizing
	{
		enum pos
		{
			LEFT,
			TOP_LEFT,
			TOP,
			RIGHT,
			TOP_RIGHT,
			BOTTOM_RIGHT,
			BOTTOM,
			BOTTOM_LEFT,
			NONE
		};
	};

	enum Style
	{
		NO_FRAME,
		TOOLBOX,
		NORMAL
	};

	enum BehaviourOnClose
	{
		DESTROY,
		INVISIBLE
	};

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
	Window(const std::string& name = "", 
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
	Window(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse pressed event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMousePressed_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse released event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseReleased_impl(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse move event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseHover_impl(MouseEvent& ev);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onGainedFocus();

	void setBehaviourOnClose(BehaviourOnClose behaviour)
	{myBehaviour = behaviour;}

	BehaviourOnClose getBehaviourOnClose() const
	{return myBehaviour;}

	void setTitle(const std::string& title) {myTitle = title;}
	const std::string& getTitle() const {return myTitle;}

	PtrTitleBar getTitleBar();

protected:
	void clickCloseButton(MouseEvent&);

protected:
	bool myIsResizing;

	bool myIsLeftResizing;
	bool myIsTopResizing;
	bool myIsTopLeftResizing;
	bool myIsRightResizing;
	bool myIsTopRightResizing;
	bool myIsBottomResizing;
	bool myIsBottomLeftResizing;
	bool myIsBottomRightResizing;

	PrivResizing::pos myResizingPosition;

	BehaviourOnClose myBehaviour;

	std::string myTitle;

	const std::string PREFIX_TITLEBAR;
};

GAIA_REGISTER_TYPE(Window)

} //end namespace

#endif