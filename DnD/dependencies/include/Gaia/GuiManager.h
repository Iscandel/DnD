#ifndef H__GUIMANAGER_030920110208__H
#define H__GUIMANAGER_030920110208__H

///////////////////////////////////////////////////////////////////////////////
// Headers-STL
///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <map>
#include <vector>
#include <stack>

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/BaseInput.h"
#include "Gaia/BaseGraphics.h"
#include "Gaia/Config.h"
#include "Gaia/KeyRepeatManager.h"
#include "Gaia/MouseClickAnalyzer.h"
#include "Gaia/WidgetFactory.h"
#include "Gaia/WidgetManager.h"
#include "Gaia/widgets/WidgetList.h"
#include "Gaia/tools/Binder.h"
#include "Gaia/tools/Exceptions.h"
#include "Gaia/tools/Singleton.h"

namespace gaia
{
class FocusWidgetManager;

/////////////////////////////////////////////////////////////////////////////////
//// \brief Manages all interactions between widgets, inputs.
/////////////////////////////////////////////////////////////////////////////////
class GAIA_DLL GuiManager : public gaia::Singleton<GuiManager>
{
public:
	friend class KeyRepeatManager;
public:
	/////////////////////////////////////////////////////////////////////////////
	//// \brief Constructor.
	/////////////////////////////////////////////////////////////////////////////
	GuiManager(void);

	///////////////////////////////////////////////////////////////////////////
	//// \brief Constructor.
	///
	///////////////////////////////////////////////////////////////////////////
	GuiManager(const Point& mousePos, BaseGraphics* gfx = NULL);

	/////////////////////////////////////////////////////////////////////////////
	//// \brief Destructor.
	/////////////////////////////////////////////////////////////////////////////
	~GuiManager(void);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Creates a new widget with the given type and associates the name.
	///
	/// \param type : Widget type.
	/// \param name : Name to give.
	///
	/// \return A smart pointer to the created widget
	///////////////////////////////////////////////////////////////////////////
	PtrWidget createWidget(const std::string& type, const std::string& name);

		///////////////////////////////////////////////////////////////////////////
	/// \brief Reload the given widget with the given type and name.
	///
	/// \param type : Widget type.
	/// \param name : Widget's name.
	///
	/// \return A smart pointer to the reloaded widget
	///////////////////////////////////////////////////////////////////////////
	PtrWidget reloadWidget(const std::string& type, const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Defines the window size.
	///
	/// GUI layouts are constructed by the user for a given resolution. When 
	/// you change the window size, a ratio is computed compared to the 
	/// reference resolution. It enables to apply some resize to the widget list.
	///
	/// \param width: Window width.
	/// \param height: Window height.
	/// \param ratioX: X ratio to define, compared to a reference width.
	/// \param ratioY: Y ratio to define, compared to a reference height.
	/////////////////////////////////////////////////////////////////////////////
	void setWindowSize(int width, int height);//, float ratioX = 1.f, float ratioY = 1.f);

	//////////////////////////////////////////////////////////////////////////
	/// \brief Returns the window width.
	///
	/// \return Window width in pixels.
	//////////////////////////////////////////////////////////////////////////
	int getWindowWidth() const {return myWidth;}

	//////////////////////////////////////////////////////////////////////////
	/// \brief Returns the window height.
	///
	/// \return Window height in pixels.
	//////////////////////////////////////////////////////////////////////////
	int getWindowHeight() const {return myHeight;}

	//////////////////////////////////////////////////////////////////////////
	/// \brief Returns the X ratio of the window, depending on the current
	/// window resolution. 
	///
	/// \return X ratio.
	///
	/// \see setWindowSize
	//////////////////////////////////////////////////////////////////////////
	double getRatioX() const;// {return myRatioX;}

	//////////////////////////////////////////////////////////////////////////
	/// \brief Returns the Y ratio of the window, depending on the current
	/// window resolution. 
	///
	/// \return Y ratio.
	///
	/// \see setWindowSize
	//////////////////////////////////////////////////////////////////////////
	double getRatioY() const;// {return myRatioY;}

	//////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget with the given name.
	///
	/// The function throw an exception if it cannot be converted to the 
	/// specified type, and a null pointer if it was not found.
	///
	/// \param name : The name of the widget to retrieve.
	///
	/// \return A smart pointer to the widget.
	//////////////////////////////////////////////////////////////////////////
	template<class T> 
	boost::shared_ptr<T> getWidget(const std::string& name)
	{
		return WidgetsManager::getInstance()->getWidget<T>(name);
	}

	//template <class TypeGen, class Classe<TypeGen> >
	//boost::shared_ptr<TypeGen> getWidget2(const std::string& name)
	//{
	//	return WidgetsManager::getInstance()->getWidget<TypeGen>(name);
	//}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget located to the given position. 
	///
	/// The function returns a null pointer if no widget was found. In the case
	/// where several widgets of same 'family' were found at this position,
	/// the function returns only the last child (the one on the top).
	///
	///	\param mousePos: mouse position to test.
	///
	/// \return A smart pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	PtrWidget getWidgetAt(const Point& posSouris);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget located to the given position. 
	///
	/// The function returns a null pointer if no widget was found. In the case
	/// where several widgets of same 'family' were found at this position,
	/// the function returns only the last child (the one on the top).
	///
	///	\param mousePos: mouse position to test.
	/// \param x: X position to test.
	/// \param y: Y position to test
	///
	/// \return A smart pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	PtrWidget getWidgetAt(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns a vector containing all the widgets located at the given
	/// position.
	///
	/// The function returns an empty vector if no one was found.
	///
	///	\param mousePos: mouse position to test.
	///
	/// \return A vector of smart pointers to the widgets.
	///////////////////////////////////////////////////////////////////////////
	std::vector<PtrWidget> getWidgetsAt(const Point& mousePos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns a vector containing all the widgets located at the given
	/// position.
	///
	/// The function returns an empty vector if no one was found.
	///
	///	\param x: x position to test.
	///
	///	\param y: y position to test.
	///
	/// \return A vector of smart pointers to the widgets.
	///////////////////////////////////////////////////////////////////////////
	std::vector<PtrWidget> getWidgetsAt(int x, int y);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the top level widget.
	///
	/// \return A smart pointer to the top level widget.
	///////////////////////////////////////////////////////////////////////////
	PtrDefaultContainer getRootWidget();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget which caught mouse inputs. If no widget
	/// has caught inputs, the function returns a null pointer
	///
	/// \return A smart pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	PtrWidget getWidgetCaughtInput();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Renvoie un vecteur contenant tous les widgets localisés aux 
	/// coordonnées passées en paramètres, un vecteur de taille nul si aucun 
	/// n'a été trouvé à cet emplacement
	///
	///	\param x: La position X de la souris
	///
	/// \param y: La position Y de la souris
	///
	/// \return Un pointeur sur le widget, un pointeur nul si aucun de trouvé
	///////////////////////////////////////////////////////////////////////////
	//void setWidgetCatchInputs(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Renvoie un vecteur contenant tous les widgets localisés aux 
	/// coordonnées passées en paramètres, un vecteur de taille nul si aucun 
	/// n'a été trouvé à cet emplacement
	///
	///	\param x: La position X de la souris
	///
	/// \param y: La position Y de la souris
	///
	/// \return Un pointeur sur le widget, un pointeur nul si aucun de trouvé
	///////////////////////////////////////////////////////////////////////////
	//void releaseInputs() {setWidgetCatchInputs(PtrWidget());}

	PtrWidget getWidgetModal();

	//void setWidgetModal(PtrWidget w);
	//void relacherWidgetModal(PtrWidget w = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Saves the current mouse position.
	///
	///	\param x: X position
	///
	/// \param y: Y position
	///////////////////////////////////////////////////////////////////////////
	void setMousePosition(int x, int y) {myMousePosition = Point(x, y);}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Saves the current mouse position.
	///
	///	\param x: X position
	///
	/// \param y: Y position
	///////////////////////////////////////////////////////////////////////////
	void setGraphics(BaseGraphics* gfx);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the current graphics engine.
	///
	///	\return A pointer to the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	BaseGraphics* getGraphics() {return myGraphics;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Marks all widgets to delete them in the next update call. This
	/// function should be used instead of clean() when you want to clean the 
	/// gui inside of a widget's callback function defined by the user. 
	/// Also resets all focus.
	///////////////////////////////////////////////////////////////////////////
	void cleanDelayed();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes all widgets, and resets all focus.
	///////////////////////////////////////////////////////////////////////////
	void clean();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Process the given event.
	///
	/// \return True if the event was handled, false if it was not, and should
	/// be reused in the program.
	///////////////////////////////////////////////////////////////////////////
	bool processEvent(BaseInput& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws all widgets.
	///////////////////////////////////////////////////////////////////////////
	void draw();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates all widgets.
	///
	/// \param elapsedTime : elasped time since the last call to update
	///////////////////////////////////////////////////////////////////////////
	void update(unsigned int elapsedTime);

	///////////////////////////////////////////////////////////////////////////
	/// \brief if true, it enables the GUI to manage key repeat itself, and 
	/// thus allows it to inject key events if required.
	///
	/// Key repeat is not active by default.
	///
	/// \param enable : True to enable key repeat, false to deactivate it.
	///////////////////////////////////////////////////////////////////////////
	void enableKeyRepeat(bool handle) {myIsKeyRepeatEnabled = handle;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the management of key is enabled or not.
	///
	/// \return true if key repeat is managed, false if it is not.
	///////////////////////////////////////////////////////////////////////////
	bool isKeyRepeatEnabled()const {return myIsKeyRepeatEnabled;}

protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles a mouse event, and redistributes it to the appropriate
	/// widget.
	///
	///	\param ev : The mouse event to consider.
	///
	/// \param mousePos : Current mouse position.
	///
	/// \return True if the event was handled and shouldn't be used again, 
	/// false if it was not used.
	///////////////////////////////////////////////////////////////////////////
	bool handleMouseEvent(MouseEvent& ev, const Point& mousePos);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Handles a keyboard event, and redistributes it to the appropriate
	/// widget.
	///
	///	\param ev : The mouse event to consider.
	///
	/// \return True if the event was handled and shouldn't be used again, 
	/// false if it was not used.
	///////////////////////////////////////////////////////////////////////////
	bool handleKeyboardEvent(KeyboardEvent& ev);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates the currently hovered widget(s) and the ones which have
	/// been just exited.
	///
	/// \param mousePosition : Current mouse position.
	///////////////////////////////////////////////////////////////////////////
	void updateWidgetsContainingMouse(const Point& mousePosition);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Updates the key repeat process, if enabled.
	///
	/// \param elapsedTime : elasped time since the last call to update
	///////////////////////////////////////////////////////////////////////////
	//void manageKeyRepeat(unsigned int elapsedTime);

protected:
	int myWidth;
	int myHeight;
	//float myRatioX;
	//float myRatioY;

	typedef boost::weak_ptr<BaseWidget> WeakPtrWidget;

	//std::vector<PtrWidget> myHoveredWidgets;
	std::vector<WeakPtrWidget> myHoveredWidgets;

	//PtrWidget MonWidgetCaptureEntrees;

	PtrDefaultContainer myRootWidget;

	FocusWidgetManager* myFocusWidgetManager;

	//La pile de widgets modaux. Seul celui au sommet est modal
	//std::stack<PtrWidget> MonWidgetModal;

	MouseClickAnalyzer myMouseClickAnalyzer;

	bool myIsKeyRepeatEnabled;

	Point myMousePosition;

	gaia::BaseGraphics* myGraphics;

	KeyRepeatManager myKeyRepeatManager;

	unsigned int myInitialKeyRepeatTime;
	unsigned int myKeyRepeatTime;
	bool myIsKeyPressed;
	KeyboardEvent myLastKeyPressedEvent;

	const unsigned int TIME_OUT_REPEAT_FIRST;
	const unsigned int TIME_OUT_REPEAT;
};

} //end namespace 

#endif