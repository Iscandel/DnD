#ifndef H__EVENT261120102001__H
#define H__EVENT261120102001__H

#include <cstdio>

namespace gaia
{
class BaseWidget;

///////////////////////////////////////////////////////////////////////////////
/// Represents a keyboard key.
///////////////////////////////////////////////////////////////////////////////
struct Keyboard
{
	enum Code
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        NUM0,
        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,
        NUM7,
        NUM8,
        NUM9, 
        ESCAPE,
        LCONTROL,
        LSHIFT,
        LALT,
        LSSYSTEM,      ///< OS specific key (left side) : windows (Win and Linux), apple (MacOS), ...
        RCONTROL,
        RSHIFT,
        RALT,
        RSYSTEM,      ///< OS specific key (right side) : windows (Win and Linux), apple (MacOS), ...
        MENU,
        LBRACKET,     ///< [
        RBRACKET,     ///< ]
        SEMICOLON,    ///< ;
        COMMA,        ///< ,
        PERIOD,       ///< .
        QUOTE,        ///< '
        SLASH,        ///< /
        BACKSLAH,
        TILDE,        ///< ~
        EQUAL,        ///< =
        DASH,         ///< -
        SPACE,
        RETURN,
        BACK,
        TAB,
        PAGEUP,
        PAGEDOWN,
        END,
        HOME,
        INSERT,
        DEL,
        ADD,          ///< +
        SUBTRACT,     ///< -
        MULTIPLY,     ///< *
        DIVIDE,       ///< /
        LEFT,         ///< Left arrow
        RIGHT,        ///< Right arrow
        UP,           ///< Up arrow
        DOWN,         ///< Down arrow
        NUMPAD0,
        NUMPAD1,
        NUMPAD2,
        NUMPAD3,
        NUMPAD4,
        NUMPAD5,
        NUMPAD6,
        NUMPAD7,
        NUMPAD8,
        NUMPAD9,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        PAUSE,

        COUNT // Keep last -- total number of keyboard keys
    };
};


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// Defines which mouse button was pressed.
///////////////////////////////////////////////////////////////////////////////
struct MouseButton
{
	enum Button
    {
        LEFT,
        RIGHT,
        MIDDLE,
        XBOUTON1,
        XBOUTON2,
		NO_BUTTON,
		END
	 };
};


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// Base class for events. Most of the time, it defines an input event.
///////////////////////////////////////////////////////////////////////////////
class Event
{
public:
	enum EventType
	{
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_MOVE,
		MOUSE_WHEEL,
		KEY_PRESSED,
		KEY_RELEASED,
		TEXT_ENTERED,
		END	///< Number of input events. Also used if the current event is not an input event.
	};

public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor
	///
	/// \param w: The widget for which the event is intended. Mostly, it is the 
	/// one which triggered the event.
	///
	/// \param evType: Event type.
	///////////////////////////////////////////////////////////////////////////
	Event(BaseWidget* w = NULL, 
		  EventType evType = Event::END)
	: myWidget(w)
	, type(evType)
	, myIsHandled(false)
	{}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the type of event.
	///
	/// \return Event type.
	///////////////////////////////////////////////////////////////////////////
	EventType getType() {return type;}

	///////////////////////////////////////////////////////////////////////////
	/// Returns a pointer to the widget for which the event is intended.
	///
	/// \return A pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	BaseWidget* getSource() {return myWidget;}

	///////////////////////////////////////////////////////////////////////////
	/// Marks the event to indicate that it has been handled and should not be
	/// be used anymore.
	///////////////////////////////////////////////////////////////////////////
	void use() {myIsHandled = true;}

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the event was handled or not.
	///
	/// \return true if the event was handled.
	///////////////////////////////////////////////////////////////////////////
	bool isHandled() const {return myIsHandled;}

//protected:
	BaseWidget* myWidget;

	EventType type;
	bool myIsHandled;
};


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// Defines a mouse event.
///////////////////////////////////////////////////////////////////////////////
class MouseEvent : public Event
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Default Constructor
	///////////////////////////////////////////////////////////////////////////
	MouseEvent() {}

	///////////////////////////////////////////////////////////////////////////
	/// Constructor
	///
	/// \param w: The widget for which the event is intended. Mostly, it is the 
	/// one which triggered the event.
	///
	/// \param evType: Event type.
	///
	/// \param x: X coordinate of the mouse.
	///
	/// \param y: Y coordinate of the mouse.
	///
	/// \param delta: Defines the amount of movement of the mouse wheel.
	///
	/// \param button: The mouse button pressed or released if relevant. If 
	/// not, it is set to NO_BUTTON
	///////////////////////////////////////////////////////////////////////////
	MouseEvent(BaseWidget* w, 
			   EventType evType, 
			   int x, 
			   int y, 
			   float delta, 
			   MouseButton::Button button)
	:Event(w, evType)
	,myX(x)
	,myY(y)
	,myWheelDelta(delta)
	,myButton(button)
	{}

	
	///////////////////////////////////////////////////////////////////////////
	/// Returns the mouse X coordinate.
	///
	/// \return X coordinate.
	///////////////////////////////////////////////////////////////////////////
	int getX() const {return myX;}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the mouse Y coordinate.
	///
	/// \return Y coordinate.
	///////////////////////////////////////////////////////////////////////////
	int getY() const {return myY;}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the mouse wheel delta.
	///
	/// \return The mouse wheel delta.
	///////////////////////////////////////////////////////////////////////////
	float getWheelDelta() const {return myWheelDelta;}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the mouse button pressed or released if relevant.
	///
	/// \return The mouse button pressed or released.
	///////////////////////////////////////////////////////////////////////////
	MouseButton::Button getButton() const {return myButton;}

//protected:
	int myX; ///< X coordinate
	int myY; ///< Y coordinate
	float myWheelDelta; ///< Mouse wheel delta.
	MouseButton::Button myButton; ///< Mouse button.
};


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// Defines a keyboard event.
///////////////////////////////////////////////////////////////////////////////
class KeyboardEvent : public Event
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///
	/// \param w: The widget for which the event is intended. Mostly, it is the 
	/// one which triggered the event.
	///
	/// \param evType: Event type.
	///
	/// \param key: Key pressed or released.
	///
	/// \param character: unicode value of the character if relevant.
	///
	/// \param shift: Shift key is pressed or not.
	///
	/// \param alt: Alt key is pressed or not.
	///
	/// \param control: Control key is pressed or not.
	///////////////////////////////////////////////////////////////////////////
	KeyboardEvent(BaseWidget* w,  
				  EventType evType, 
				  Keyboard::Code key, 
				  int character, 
				  bool shift, 
				  bool alt, 
				  bool control)
	:Event(w, evType)
	,myKey(key)
	,unicode(character)
	,isShiftPressed(shift)
	,isAlttPressed(alt)
	,isControlPressed(control)
	{}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the key code of the key pressed or released.
	///
	/// \return The key code.
	///////////////////////////////////////////////////////////////////////////
	Keyboard::Code getKey() const {return myKey;}

	///////////////////////////////////////////////////////////////////////////
	/// Returns the unicode value of the character, if relevant.
	///
	/// \return The unicode value of the character.
	///////////////////////////////////////////////////////////////////////////
	int getCharacter() const {return unicode;}
//protected:
	Keyboard::Code myKey;	///< Key code.
	int unicode;			///< Unicode value.
	bool isControlPressed;	///< Control pressed ?
	bool isShiftPressed;	///< Shift pressed ?
	bool isAlttPressed;		///< Alt pressed ?
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// Defines a widget visibility event.
///////////////////////////////////////////////////////////////////////////////
class VisibilityEvent : public Event
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///
	/// \param w: The widget for which the event is intended. Mostly, it is the 
	/// one which triggered the event.
	///
	/// \param visible: Indicates if the widget if now visible or not.
	///////////////////////////////////////////////////////////////////////////
	VisibilityEvent(BaseWidget* w, bool visible)
	:Event(w)
	,myIsVisible(visible)
	{}

	///////////////////////////////////////////////////////////////////////////
	///  Indicates if the widget if now visible or not.
	///
	/// \return true if the widget is visible, false if not.
	///////////////////////////////////////////////////////////////////////////
	bool isVisible() const {return myIsVisible;}

protected:
	bool myIsVisible;
};

} //end namespace

#endif
