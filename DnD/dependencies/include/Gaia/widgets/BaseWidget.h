#ifndef H__BASEWIDGET_100920110149__H
#define H__BASEWIDGET_100920110149__H

///////////////////////////////////////////////////////////////////////////////
/// Headers-External
///////////////////////////////////////////////////////////////////////////////
#include <boost/function.hpp>
#include <boost/function_equal.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
/// Headers-STL
///////////////////////////////////////////////////////////////////////////////
#include <vector>

///////////////////////////////////////////////////////////////////////////////
/// Headers-GUI
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/BaseGraphics.h"
#include "Gaia/Config.h"
#include "Gaia/Point.h"
#include "Gaia/Rectangle.h"
//#include "Gaia/WidgetList.h"
#include "Gaia/PropertySystem.h"
#include "Gaia/Event.h"
#include "Gaia/tools/Exceptions.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/tools/Binder.h"
#include "Gaia/tools/NonCopyable.h"
#include "Gaia/widgets/WidgetStaticType.h"
#include "Gaia/LayoutInfos.h"

namespace gaia
{
class IWidgetRenderer;
class BaseWidget;
class FocusWidgetManager;

typedef boost::shared_ptr<BaseWidget> PtrWidget;

///////////////////////////////////////////////////////////////////////////////
/// \brief We register the static BaseWidget type.
///////////////////////////////////////////////////////////////////////////////
GAIA_REGISTER_TYPE(BaseWidget)

//////////////////////////////////////////////////////////////////////////////
/// \brief Base class for all widgets.
///
/// If you want to create your own derived widgets, take into account these
/// advices:
///
/// -All derived widgets should have their own static member variable called
/// myWidgetType.
///
/// -You are not forced to use a widget renderer. You can override the draw
/// function, but don't forget to draw children, to clip the drawing, and to 
/// set the relative origin of the graphic (if necessary).
///
/// -If you want to extend existing widgets, you should also extend their 
/// corresponding widget renderer from widget renderer whose name starts
/// with Base<ParentWidgetName>
//////////////////////////////////////////////////////////////////////////////
class GAIA_DLL BaseWidget : public NonCopyable, public boost::enable_shared_from_this<BaseWidget>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Defines the widget state relative to mouse interaction with the widget.
	///////////////////////////////////////////////////////////////////////////
	enum WidgetState {NORMAL, HOVER, CLICKED};

	///////////////////////////////////////////////////////////////////////////
	/// Defines some alignment for derived classes.
	///////////////////////////////////////////////////////////////////////////
	enum HorizontalAlignment {LEFT, CENTER, RIGHT};

/// Many typedefs to simplify function binding.
protected:
	typedef FunctionHandler<MouseEvent&>  MouseFunction;
	//typedef FunctionHandler<MouseEvent&> MouseFunction;
	//typedef FunctionHandler<MouseEvent&>  MouseFunction;
	typedef FunctionHandler<KeyboardEvent&>  KeyboardFunction;
	//typedef FunctionHandler<KeyboardEvent&>  KeyboardFunction;
	typedef FunctionHandler<VisibilityEvent&>  VisibilityFunction;
	typedef FunctionHandler<Event&>  EnterExitFunction;
	typedef FunctionHandler<Event&>  DimensionsChangedFunction;
	typedef FunctionHandler<Event&>  GainedLostFocusFunction;
	typedef FunctionHandler<Event&>  GenericFunction;
	//typedef boost::function1<void, MouseEvent&> MouseButtonFunction;
	//typedef boost::function1<void, MouseEvent&> MouseHoverFunction;
	//typedef boost::function1<void, MouseEvent&> MouseWheelFunction;
	//typedef boost::function1<void, KeyboardEvent&> KeyboardFunction;
	//typedef boost::function1<void, KeyboardEvent&> TextFunction;
	//typedef boost::function1<void, VisibilityEvent&> VisibilityFunction;
	//typedef boost::function1<void, Event&> EnterExitFunction;
	//typedef boost::function1<void, Event&> DimensionsChangedFunction;
	//typedef boost::function1<void, Event&> GainedLostFocusFunction;
	//typedef boost::function1<void, Event&> GenericFunction;

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
	BaseWidget(const std::string& name = "", int x = 0, int y = 0, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param name: Widget name. Must be absolutely unique.
	///
	/// \param dimensions: Rectangle defining the widget size (top left 
	/// position is relative to parent widget, or the screen if the widget is 
	/// the top level widget).
	///////////////////////////////////////////////////////////////////////////
	BaseWidget(const std::string& name, const IntRect& dimensions);

	///////////////////////////////////////////////////////////////////////////
	// \brief Virtual destructor.
	///////////////////////////////////////////////////////////////////////////
	virtual ~BaseWidget(void);
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the new dimensions of the widget (position + size). 
	/// Negative values of width and height are set to 0.
	///
	/// \param dim: Rectangle defining the position relatively to the parent
	/// widget, and the new size.
	///
	/// \see void setDimensions(int x, int y, int largeur, int hauteur)
	///////////////////////////////////////////////////////////////////////////
	void setDimensions(const IntRect& dim);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the new dimensions of the widget (position + size).
	/// Negative values of width and height are set to 0.
	///
	/// \param dim: Rectangle defining the position relatively to the parent
	/// widget, and the new size.
	///
	/// \see void setDimensions(const IntRect& dim)
	///////////////////////////////////////////////////////////////////////////
	void setDimensions(int x, int y, int largeur, int hauteur);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets relative dimensions to the widget relatively to its parent 
	/// (or the screen if no parent). 
	///
	/// The dimensions are given in percentage :
	/// 0.0 to 1.0. If the widget has relative dimensions, it will be resized 
	/// if the parent size or the screen size changes.
	///
	/// \param dim: Dimensions (position + size) given with values between 
	/// 0.0 and 1.
	///////////////////////////////////////////////////////////////////////////
	//void setRelativeDimensions(const Rect<double>& dim);// {myRelativeDimensions = dim;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief returns relative dimensions of the widget relatively to its parent 
	/// (or the screen if no parent). 
	///
	/// The dimensions are given in percentage :
	/// 0.0 to 1.0. If the widget has relative dimensions, it will be resized 
	/// if the parent size or the screen size changes.
	///
	/// \return dim: Dimensions (position + size) given with values between 
	/// 0.0 and 1.
	///////////////////////////////////////////////////////////////////////////
	//const Rect<double>& getRelativeDimensions() const {return myRelativeDimensions;}

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the widget has relative dimensions or not.
	///
	/// \return true if the widget has relative dimensions, false if not.
	///////////////////////////////////////////////////////////////////////////
	//bool hasRelativeDimensions() const;

	///////////////////////////////////////////////////////////////////////////
	/// Returns the widget name.
	/// 
	/// \return The widget name.
	///////////////////////////////////////////////////////////////////////////
	const std::string& getName() const {return myName;}

	///////////////////////////////////////////////////////////////////////////
	/// Set the name of the widget
	///
	/// \param name: The name to set.
	///////////////////////////////////////////////////////////////////////////
	void setName(const std::string& name) {myName = name;}
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a property shared between all the widgets of the same class.
	///
	/// The template parameter T defines the widget class for which you want 
	/// to add the property, and PROP defines the property class name.
	/// Remark: If a property with the same name already exists for this type
	/// of widget, an exception is thrown.
	///
	/// \param name: The name set to the property.
	/// \see bool replaceSharedProperty(const std::string& name)
	///////////////////////////////////////////////////////////////////////////
	template<class T, class PROP>
	static void addSharedProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a property for the instancied object (typically used by widget
	/// renderer).
	///
	/// \param prop: A smart pointer to the property to add.
	///////////////////////////////////////////////////////////////////////////
	void addProperty(properties::PtrProperty p);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a shared property, or replace it if it exists.
	///
	/// The template parameter T defines the widget class for which you want to add
	/// the property, and PROP defines the property class name.
	///
	/// \param name: The name set to the property.
	/// \see bool addSharedProperty(const std::string& name)
	///////////////////////////////////////////////////////////////////////////
	template<class T, class PROP>
	static bool replaceSharedProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set the value of the property to the widget identfied by its name.
	/// 
	/// \param name: name of the widget targeted by the property.
	/// \param value: String value to set
	///////////////////////////////////////////////////////////////////////////
	void setProperty(const std::string& name, const std::string& value);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the value of property identified by its name.
	/// 
	/// \param name : Name of the property.
	/// \return String value of the property
	///////////////////////////////////////////////////////////////////////////
	std::string getProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a shared property for the widget with template type T.
	///
	/// \param name : Name of the property to delete.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	static bool deleteSharedProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Deletes a property for the current object.
	///
	/// \param name : Name of the property to delete.
	///////////////////////////////////////////////////////////////////////////
	bool deleteProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Enables the widget to handle the double click.
	///
	/// \param handle: true if the widget should handle the double click, false
	/// if not.
	///////////////////////////////////////////////////////////////////////////
	void enableDoubleClick(bool handle) {myHandleDoubleClick = handle;}

	///////////////////////////////////////////////////////////////////////////
	/// Indicates whether the widget handles double click.
	///////////////////////////////////////////////////////////////////////////
	bool isDoubleClickEnabled() const {return myHandleDoubleClick;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Enables the widget to get all the mouse inputs, even those which 
	/// are not in the widget area. 
	///
	/// This special state finished when calling the associated release function.
	///
	/// \see void releaseMouseInputs()
	///////////////////////////////////////////////////////////////////////////
	void catchMouseInputs();

	///////////////////////////////////////////////////////////////////////////
	/// \brief If the widget has captured the mouse inputs, it stops the capture.
	///////////////////////////////////////////////////////////////////////////
	void releaseMouseInputs();

public:	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget and its children.
	///
	/// \param X: X coordinate of the parent widget (0 if no parent).
	///	\param Y: Y coordinate of the parent widget (0 if no parent).
	///////////////////////////////////////////////////////////////////////////
	virtual void draw(int x = 0, int y = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Redraws the widget.
	///////////////////////////////////////////////////////////////////////////
	void invalidate() 
	{
		myNeedRedraw = true;
		if(myGraphics)
			myGraphics->invalidate();
		//Redessiner gui ?
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws child widgets.
	///
	/// \param X: X coordinate of the parent widget (0 if no parent).
	///	\param Y: Y coordinate of the parent widget (0 if no parent).
	///////////////////////////////////////////////////////////////////////////
	void drawChildren(int x = 0, int y = 0);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse pressed event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMousePressed(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse released event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseReleased(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse double click event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleDoubleClick(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse move event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseHover(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a mouse wheel event.
	///
	/// \param ev: The mouse event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleMouseWheel(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a key pressed event.
	///
	/// \param ev: The keyboard event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleKeyPressed(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a key released event.
	///
	/// \param ev: The keyboard event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleKeyReleased(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Handles in a generic way the response to a text entered event.
	///
	/// \param ev: The keyboard event triggered.
	///
	/// \return true if the event was handled and shoudn't be used again.
	///////////////////////////////////////////////////////////////////////////////
	bool handleTextEntered(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the couple (x, y) is inside the widget. (x,y) 
	/// must be in the coordinate system of the widget.
	///
	/// \param x: X coordinate to test.
	/// \param y: Y coordinate to test.
	///
	///	\return true if the couple (x,y) is inside the widget, false if not.
	///////////////////////////////////////////////////////////////////////////
	virtual bool testCollision(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set the current widget state.
	/// 
	/// \param state: State to set.
	///////////////////////////////////////////////////////////////////////////
	virtual void setWidgetState(WidgetState state);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the current widget state.
	///
	/// \return The widget state.
	///////////////////////////////////////////////////////////////////////////
	WidgetState getWidgetState() const {return myWidgetState;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts the widget state from an enum value to a string 
	/// representation.
	///
	/// The different possible states are : normal, hover, click.
	/// An exception is thrown is the state given in argument is not valid
	/// (should not occur).
	///
	/// \return The string widget state.
	///////////////////////////////////////////////////////////////////////////
	std::string getStrWidgetState();

	///////////////////////////////////////////////////////////////////////////
	// \brief Returns the widget dimensions
	///////////////////////////////////////////////////////////////////////////
	virtual const IntRect& getWidgetDimensions() {return myDimensions;}

	///////////////////////////////////////////////////////////////////////////
	// \brief Makes this widget the focus owner.
	///////////////////////////////////////////////////////////////////////////
	virtual void requestFocus(bool b);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Creates a widget and adds it as a child.
	/// 
	/// \param type: Type of the widget to create.
	/// \param name: Unique name of the widget to create.
	///
	/// \return A smart pointer to the created widget.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrWidget createChild(const std::string& type, const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Reloads the specified child.
	/// 
	/// \param type: Type of the widget to reload (necessary to affect the renderer).
	/// \param name: Unique name of the widget to reload.
	///
	/// \return A smart pointer to the reloaded widget.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrWidget reloadChild(const std::string& type, const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds the given widget as a child widget.
	/// 
	/// \param w: the widget to add as a child of this one.
	///////////////////////////////////////////////////////////////////////////
	virtual void add(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Checks if the widget identified by its name is a child of this one.
	///
	/// \param name: Name of the widget to test.
	///
	/// \return true if it exists, false if not.
	///////////////////////////////////////////////////////////////////////////
	bool isChildPresent(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the requested child. 
	/// 
	///	The template parameter T corresponds to the requested class. If the
	/// widget. If the widget is not found, a null pointer is returned.
	///
	/// \param name: Name of the child.
	///
	/// \return A smart pointer to the child, converted into the appropriate
	/// type
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	boost::shared_ptr<T> getChild(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns all children. 
	/// 
	///	The template parameter T corresponds to the requested class. If the
	/// widget. If the widget is not found, a null pointer is returned.
	///
	/// \return A vector of smart pointers to the children.
	///////////////////////////////////////////////////////////////////////////
	std::vector<PtrWidget> getChildren() {return myChildren;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Look for a child at the given positon (x, y). (x,y) must be 
	/// in the widget coordinate system. If several widgets are candidate, the 
	/// returned one is the top level one.
	///
	/// \param x: X position.
	/// \param y: Y position.
	/// 
	/// \return The found widget, a null pointer in the other case.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrWidget getChildAt(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Looks for children at the given positon (x, y). (x,y) must be 
	/// in the widget coordinate system.
	///
	/// \param x: X position.
	/// \param y: Y position.
	/// 
	/// \return vector of pointers to the found widgets, an empty vector in the 
	/// other case.
	///////////////////////////////////////////////////////////////////////////
	std::vector<PtrWidget> getChildrenAt(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget given as a parameter is an ancestor of the
	/// current one.
	///
	///	\param widget: the possible ancestor of this one.
	///
	/// \return true if the current widget is a descendant of the widget to 
	/// test, false if not.
	///////////////////////////////////////////////////////////////////////////
	bool isDescendantFrom(PtrWidget widget);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes a child widget.
	///
	/// \param w: child to remove.
	///
	/// \return true if the widget was found and then removed, false if not.
	///////////////////////////////////////////////////////////////////////////
	/*virtual*/ bool remove(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes a child widget.
	///
	/// \param i: index of the widget to remove in the children list. 
	///
	/// \return true if the widget was found and then removed, false if not.
	///////////////////////////////////////////////////////////////////////////
	/*virtual*/ bool remove(unsigned int i);

	///////////////////////////////////////////////////////////////////////////
	/// Removes all children.
	///////////////////////////////////////////////////////////////////////////
	virtual void removeChildren() {myChildren.clear();}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Moves the given child to the top of the children list.
	/// 
	/// \param i: index of the child to move.
	///////////////////////////////////////////////////////////////////////////
	//void moveChildToTop(int i);

	void moveToForeground();
	void moveToBackground();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates the widget.
	/// 
	/// \param elapsedTime: elapsed time since the last call to update().
	///////////////////////////////////////////////////////////////////////////
	virtual void update(unsigned int elapsedTime);

public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeMousePressed(const MouseFunction& function)//void (Class::*function)(T), Instance instance = NULL) 
	{
		//if(instance == NULL)
		//E_onMousePressed = bind1(function, instance);
		E_onMousePressed = function;
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeMouseReleased(const MouseFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onMouseReleased = function;}//bind1(function, instance);} 

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeDoubleClick(const MouseFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onDoubleClick = function;}//bind1(function, instance);} //Bouton, x, y

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you gives a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeMouseHover(const MouseFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onMouseHover = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeMouseWheel(const MouseFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onMouseWheel = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///Imagebox TextBox
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeKeyPressed(const KeyboardFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onKeyPressed = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeKeyReleased(const KeyboardFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onKeyReleased = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you gives a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeTextEntered(const KeyboardFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onTextEntered = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeVisible(const VisibilityFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onVisibiliy = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeWidgetEntered(const EnterExitFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onEnter = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeWidgetExited(const EnterExitFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onExit = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeDimensionsChanged(const GenericFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onDimensionsChanged = function;}//bind1(function, instance);}
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you give a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeGainedFocus(const GenericFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onGainedFocus = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Subscribes to the corresponding event. The function given as a parameter
	/// will be called when the event is triggered.
	///
	/// \param function: A function pointer
	///
	/// \param instance: Pointer to the associated object. If you gives a free
	/// function, don't specify this argument.
	///////////////////////////////////////////////////////////////////////////
	//template<class T, class Class, class Instance>
	void subscribeLostFocus(const GenericFunction& function)//void (Class::*function)(T), Instance instance)
	{E_onLostFocus = function;}//bind1(function, instance);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///////////////////////////////////////////////////////////////////////////
	virtual void onDestruction(); 

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onMousePressed(MouseEvent& ev); 

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onMouseReleased(MouseEvent& ev); 

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onDoubleClick(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onMouseHover(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onMouseWheel(MouseEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onKeyPressed(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onKeyReleased(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onTextEntered(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onVisibility(VisibilityEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	///\brief  This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onWidgetExited();

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onWidgetEntered();

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onDimensionsChanged();

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onGainedFocus();

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function is called when the corresponding event is triggered.
	/// If a subscription was done, it calls the function previously given by
	/// user.
	///
	/// \param ev: The corresponding mouse event.
	///////////////////////////////////////////////////////////////////////////
	virtual void onLostFocus();
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Shows or hides the widget.
	/// 
	/// \param visible: if true, shows the widget. If false, hides it. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setVisible(bool visible);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set the widget modal or not.
	/// 
	/// \param modal: if true, the widget will be modal. If false, it won't be
	/// anymore.
	///////////////////////////////////////////////////////////////////////////
	void setModal(bool modal);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Enables or disables the widget. An active widget can respond to user 
	/// input and generate events.
	///
	/// \param enable: if true, activates this widget. If not, deactivates it.
	///////////////////////////////////////////////////////////////////////////
	void setEnabled(bool enable) {myIsEnabled = enable;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Used by renderers to determine which areas of the widget should be drawn.
	///
	/// \return true if the widget is opaque, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isOpaque() const {return myIsOpaque;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines if the widget is opaque.
	///
	/// \param opaque: true if the widget is opaque, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	void setOpaque(bool opaque) {myIsOpaque = opaque;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the top left corner position of the widget.
	/// 
	/// \param x: X position
	/// \param y: Y position
	///////////////////////////////////////////////////////////////////////////
	void setPosition(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the widget's parent.
	///
	/// \param parent: The parent to set.
	///////////////////////////////////////////////////////////////////////////
	void setParent(BaseWidget* parent) {myParent = parent;}

	///////////////////////////////////////////////////////////////////////////
	// \brief Returns the widget's parent. Returns NULL if it doesn't exist.
	///////////////////////////////////////////////////////////////////////////
	BaseWidget* getParent() {return myParent;}
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether this widget is visible (when its parent is visible).
	/// 
	/// \return true if the widget is really visible, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isVisible() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether this widget is modal.
	///
	/// \return true if the widget is modal, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isModal() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether this widget is enabled.
	///
	/// \return true if the widget is enabled, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isEnabled() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether this widget has the focus.
	///
	/// \return true if the widget has the focus, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool hasFocus() const;

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines whether this widget can receive the focus or not.
	///
	/// \param b: if true, the widget can receive the focus. If false, it 
	/// cannot
	///////////////////////////////////////////////////////////////////////////
	void setFocusable(bool b) {myIsFocusable = b;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether this widget can receive focus or not.
	///
	/// \return b: true if the widget can receive the focus, false if it 
	/// cannot
	///////////////////////////////////////////////////////////////////////////
	bool isFocusable() const {return myIsFocusable;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns a pointer to the child which owns the focus. If no child has 
	/// the focus, it returns a null pointer.
	///
	/// \return A smart pointer to the child with the focus.
	///////////////////////////////////////////////////////////////////////////
	PtrWidget getFocusedChild();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the X coordinate (top left) of the widget relatively to his 
	/// parent relatively to the screen if it has no parent).
	///
	/// \return The X position of this widget.
	///////////////////////////////////////////////////////////////////////////
	int getX() const {return myDimensions.x;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the Y coordinate (top left) of the widget relatively to his 
	/// parent relatively to the screen if it has no parent).
	///
	/// \return The Y position of this widget.
	///////////////////////////////////////////////////////////////////////////
	int getY() const {return myDimensions.y;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the width of the widget.
	///
	/// \return The width.
	///////////////////////////////////////////////////////////////////////////
	int getWidth() const {return myDimensions.width;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the height of the widget.
	///
	/// \return The height.
	///////////////////////////////////////////////////////////////////////////
	int getHeight() const {return myDimensions.height;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget must be destroyed. If it is the case, it
	/// will be deleted during the next GUI update step.
	///
	/// \return true if the widget must be destroyed, false if not.
	///////////////////////////////////////////////////////////////////////////
	bool mustBeDestroyed() const {return myToDestroy;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Marks the widget to be destroyed soon.
	///////////////////////////////////////////////////////////////////////////
	virtual void destroy();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts the absolute coordinates given by the mouse position into 
	/// coordinates relatively to the widget coordinate system.
	///
	/// \param mousePos: The mouse position.
	///////////////////////////////////////////////////////////////////////////
	Point convertToMyCoordinates(const Point& mousePos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the widget renderer to be used by this widget. The previous one
	/// (if exists) will be destroyed, so use dynamically allocated objects.
	///
	/// \param wr: A pointer to the widget renderer to set.
	///////////////////////////////////////////////////////////////////////////
	virtual void setWidgetRenderer(IWidgetRenderer* wr);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns a pointer to the widget renderer used by this widget.
	///
	/// \param wr: A pointer to the widget renderer to set.
	///////////////////////////////////////////////////////////////////////////
	IWidgetRenderer* getWidgetRenderer() {return myRenderer;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the graphic engine used by this widget. 
	///
	/// This function shouldn't be called in normal usage. No desallocation is 
	/// done here, because the graphics is common to all widgets.
	///
	/// \param Gfx : Pointer to the graphics.
	///////////////////////////////////////////////////////////////////////////
	virtual void setGraphics(BaseGraphics* Gfx);

	///////////////////////////////////////////////////////////////////////////
	/// Returns a pointer to the current graphics.
	///
	/// \return A pointer to the current graphics.
	///////////////////////////////////////////////////////////////////////////
	BaseGraphics* getGraphics() {return myGraphics;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the focusWidgetManager to be used by this widget. This function
	/// shoudn't be called in normal usage.
	///
	/// \param manager: A pointer to the FocusWidgetManager to be used.
	///////////////////////////////////////////////////////////////////////////
	void affectFocusWidgetManager(FocusWidgetManager* manager);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the coordinates of the widget relatively to the screen.
	///
	/// \return The absolute coordinates.
	///////////////////////////////////////////////////////////////////////////
	IntRect getScreenCoordinates();

	//void setLayoutInfos(const LayoutInfos& infos) {myLayoutInfos = infos;}
	void setLayoutInfos(PtrLayoutInfos infos = PtrLayoutInfos());

	PtrLayoutInfos getLayoutInfos() const {return myLayoutInfos;}

	void adjustClippingArea();

	void propagateEventsToChildren(bool propagate) {myPropagateEventsToChildren = propagate;}

	bool areEventsPropagatedToChildren() const {return myPropagateEventsToChildren;;}
	
protected:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMousePressed_impl(MouseEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseReleased_impl(MouseEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleDoubleClick_impl(MouseEvent& ev){ev.use(); return true;}

	//////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseHover_impl(MouseEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// mouse event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleMouseWheel_impl(MouseEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// keyboard event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleKeyPressed_impl(KeyboardEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// keyboard event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleKeyReleased_impl(KeyboardEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Can be overriden by children. Handles in a generic way the response to a 
	/// keyboard event.
	///////////////////////////////////////////////////////////////////////////////
	virtual bool handleTextEntered_impl(KeyboardEvent& ev){ev.use(); return true;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Copies properties from shared properties to object properties.
	///////////////////////////////////////////////////////////////////////////////
	template<class T>
	void copyProperties();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Resizes the given widget (should be a child), according to this
	/// child's relative dimensions (and only if it has relative dimensions).
	///
	/// \param toResize : The child widget to resize.
	///////////////////////////////////////////////////////////////////////////
	//void resizeChildIfRelativeDim(PtrWidget toResize);

	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Resizes the widget according to the layout informations it owns.
	///////////////////////////////////////////////////////////////////////////
	void resizeFromLayout();
	
public:
	///Widget type
	//static const std::string myWidgetType;

//private:
//	const BaseWidget& operator = (const BaseWidget&);
//	BaseWidget(const BaseWidget&);

protected:
	///Shared properties
	static PropertySystem mySharedPropertySystem;
	//Les propriétés partagées
	PropertySystem myPropertySystem;
	///Indicates whether the widget is visible
	bool myIsVisible;
	///Indicates whether the widget is modal
	bool myIsModal;
	///Indicates whether the widget is enabled
	bool myIsEnabled;
	///Indicates whether the widget has focus
	bool myHasFocus;
	///Indicates whether the widget can receive the focus
	bool myIsFocusable;
	///Widget size
	IntRect myDimensions;
	///Relative dimensions relatively to parent widget
	//Rect<double> myRelativeDimensions;
	//Nom du widget
	std::string myName;
	///Parent widget
	BaseWidget* myParent;
	//Widget state
	WidgetState myWidgetState;
	///Indicates whether the widget handles double click
	bool myHandleDoubleClick;
	///Indicates wether the widget distributes events to its children (for inputs capture)
	bool myPropagateEventsToChildren;

	///Dummy for properties
	std::string myDummyWidgetType;

	///Indicates whether the widget is opaque
	bool myIsOpaque;

	///Time indicator
	unsigned int myTimeAccumulator;

	bool myToDestroy;
	
	std::vector<PtrWidget> myChildren;

	IWidgetRenderer* myRenderer;

	BaseGraphics* myGraphics;

	FocusWidgetManager* myFocusWidgetManager;

	PtrLayoutInfos myLayoutInfos;

	bool myNeedRedraw;

	bool myIsForegroundWidget;
	
	MouseFunction E_onMousePressed;
	MouseFunction E_onMouseReleased;
	MouseFunction E_onDoubleClick;
	MouseFunction E_onMouseHover;
	MouseFunction E_onMouseWheel;
	KeyboardFunction E_onKeyPressed;
	KeyboardFunction E_onKeyReleased;
	KeyboardFunction E_onTextEntered;
	VisibilityFunction E_onVisibiliy;
	EnterExitFunction E_onEnter;
	EnterExitFunction E_onExit;
	DimensionsChangedFunction E_onDimensionsChanged;
	GainedLostFocusFunction E_onGainedFocus;
	GainedLostFocusFunction E_onLostFocus;
	GenericFunction E_onDestruction;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T, class PROP>
void BaseWidget::addSharedProperty(const std::string& name)
{
	if(mySharedPropertySystem.exists(getStaticType<T>(), name))//T::myWidgetType, name))
		throw GuiException("Property " + name + " already exists and cannot be added.");
		
	properties::PtrProperty prop(new PROP(name));
	mySharedPropertySystem.addProperty(getStaticType<T>(), prop);//T::myWidgetType, prop);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T, class PROP>
bool BaseWidget::replaceSharedProperty(const std::string& name)
{
	properties::PtrProperty prop(new PROP(name));

	bool res = mySharedPropertySystem.deleteProperty(getStaticType<T>(), prop->getName());
	mySharedPropertySystem.addProperty(getStaticType<T>(), prop);//T::myWidgetType, prop);

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
bool BaseWidget::deleteSharedProperty(const std::string& name)
{
	return mySharedPropertySystem.deleteProperty(getStaticType<T>(), name);//T::myWidgetType, name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
boost::shared_ptr<T> BaseWidget::getChild(const std::string& name)
{
	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		if(myChildren[i]->getName() == name)
		{
			PtrWidget w = myChildren[i];
#ifdef _DEBUG
			boost::shared_ptr<T> res = boost::dynamic_pointer_cast<T>(w);
			if(res == NULL)
			{
				throw GuiException("Child widget " + name + 
					" cannot be converted");
			}
			return res;
#else
			return boost::dynamic_pointer_cast<T>(w);
#endif
		}
	}

	ILogger::log(ILogger::ERRORS) << "Widget " << name << " not found\n";
	return boost::shared_ptr<T>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
template<class T>
void BaseWidget::copyProperties()
{
	std::vector<properties::PtrProperty> props = 
		mySharedPropertySystem.getProperties(getStaticType<T>());//T::myWidgetType);
	for(unsigned int i = 0; i < props.size(); i++)
	{
		myPropertySystem.addProperty(myDummyWidgetType, props[i]);
	}
}


//parent->onChildPositionChanged();
//

//void resizeAreas()
//{
//	for(unsigned int i = 0; i < myLayoutAreas.size(); i++)
//	{
//		std::pair<double, double> pos = myLayoutAreas[i].parsePos(myWidget);
//		double width = myLayoutAreas[i].parseWidth(myWidget);
//		double height = myLayoutAreas[i].parseHeight(myWidget);
//
//		myAreas[i] = IntRect(static_cast<int>(pos.first),
//							 static_cast<int>(pos.second),
//							 static_cast<int>(width),
//							 static_cast<int>(height));
//	}
//}



} //end namespace

#endif
