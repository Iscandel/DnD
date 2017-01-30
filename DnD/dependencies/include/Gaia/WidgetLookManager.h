#ifndef H__WIDGETLOOKMANAGER__200620112130__H
#define H__WIDGETLOOKMANAGER__200620112130__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include <map>

#include "Gaia/tools/Singleton.h"
#include "Gaia/WidgetLook.h"

namespace gaia
{
class WidgetLook;

///////////////////////////////////////////////////////////////////////////////
/// \brief Manager for widget looks.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL WidgetLookManager :
	public gaia::Singleton<WidgetLookManager>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the widget look associated to the requested widget.
	/// 
	/// \param widgetName : Name of the widget.
	///////////////////////////////////////////////////////////////////////////
	WidgetLook* getLook(const std::string& nomWidget);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Registers a new widget look in the manager.
	///
	/// \param widgetName : The Widget associated to the look.
	/// \param look : The look to add.
	///////////////////////////////////////////////////////////////////////////
	void addLook(const std::string& widgetName, const WidgetLook& look);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Resets the manager removing all looks.
	///////////////////////////////////////////////////////////////////////////
	void clearLooks();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Sets the preferred resolution relative to the current look and
	/// feel.
	///
	/// \param x : X resolution.
	/// \param y : Y resolution.
	///////////////////////////////////////////////////////////////////////////
	void setPreferredResolution(int x, int y)
	{
		myPreferredResolution.x = x;
		myPreferredResolution.y = y;
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the preferred X resolution relative to the current look 
	/// and feel.
	///
	/// \return X resolution.
	///////////////////////////////////////////////////////////////////////////
	int getPreferredX() const {return myPreferredResolution.x;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the preferred Y resolution relative to the current look 
	/// and feel.
	///
	/// \return Y resolution.
	///////////////////////////////////////////////////////////////////////////
	int getPreferredY() const {return myPreferredResolution.y;}

protected:
	std::map<std::string, WidgetLook> myLooks; ///< Look list.

	Point myPreferredResolution; ///< Current preferred resolution.
};

};

#endif