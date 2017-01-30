#ifndef H__WIDGETSMANAGER_100920111722__H
#define H__WIDGETSMANAGER_100920111722__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/WidgetList.h"
#include "Gaia/WidgetFactory.h"
#include "Gaia/tools/Exceptions.h"
#include "Gaia/tools/Singleton.h"

#include <string>
#include <map>

namespace gaia
{
class GAIA_DLL WidgetsManager :
	public Singleton<WidgetsManager>
{
public:
	typedef std::map<std::string, PtrWidget> WidgetMap;

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
	/// \brief Affects the look the specified widget
	///
	/// \param widget : Widget considered.
	/// \param type : Widget type.
	///
	///////////////////////////////////////////////////////////////////////////
	void affectLook(PtrWidget widget, const std::string& type);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Registers the widget in the manager.
	///
	/// \param w : The widget to register
	///////////////////////////////////////////////////////////////////////////
	bool registerWidget(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes the widget from the manager.
	/// 
	/// \param name : Widget name.
	///
	/// \return true if it was successfully removed, false it if was not.
	///////////////////////////////////////////////////////////////////////////
	bool removeWidget(const std::string& nom);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes the widget from the manager.
	/// 
	/// \param w : Widget to remove.
	///
	/// \return true if it was successfully removed, false it if was not.
	///////////////////////////////////////////////////////////////////////////
	bool removeWidget(PtrWidget w);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes all the widgets which only exist in the widget manager.
	///
	/// Nb: The root widget is duplicated in a member variable of GuiManager, 
	/// so it is not unique.
	///////////////////////////////////////////////////////////////////////////
	void removeUniqueWidgets();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes all the widgets.
	///////////////////////////////////////////////////////////////////////////
	void clean();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns all the widgets.
	///
	/// \return A vector containing smart pointers to all the widgets.
	///////////////////////////////////////////////////////////////////////////
	std::vector<PtrWidget> getAllWidgets();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget corresponding to the given name.
	///
	/// If the widget cannot be casted to the right type, an exception is thrown.
	/// If it cannot be found, a null pointer is returned.
	///
	///	\param name : Widget name.
	///
	/// \return A smart pointer to the widget.
	///////////////////////////////////////////////////////////////////////////
	template<class T> 
	boost::shared_ptr<T> getWidget(const std::string& name)
	{
		std::map<std::string, PtrWidget>::iterator it = myWidgets.find(name);
		
		if(it != myWidgets.end())
		{
#ifdef _DEBUG
			//assert(boost::dynamic_pointer_cast<T>(it->second) != 0);
			boost::shared_ptr<T> res = boost::dynamic_pointer_cast<T>(it->second);
			if(res == NULL)
			{
				throw GuiException("Widget " + name + " cannot be converted");
			}
			return res;
#else
			return boost::dynamic_pointer_cast<T>(it->second); //change to static
#endif
		}
		
		ILogger::log(ILogger::ERRORS) << "Widget " << name << " not found\n";
		return boost::shared_ptr<T>();
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Indicates whether the widget exists.
	///
	/// \param name : Widget name.
	///
	/// \return true if the widget was found, false if it was not found.
	///////////////////////////////////////////////////////////////////////////
	bool exists(const std::string& name);

	void removeDestructedWidgets();

protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Generates a unique widget name.
	///
	/// \return An automatic and unique widget name.
	///////////////////////////////////////////////////////////////////////////
	std::string generateUniqueName();

	std::map<std::string, PtrWidget> myWidgets;
};

};

#endif