#ifndef H__PROPERTY_070920112357_H
#define H__PROPERTY_070920112357_H

///////////////////////////////////////////////////////////////////////////////
// Headers-STL
///////////////////////////////////////////////////////////////////////////////
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Headers-external
///////////////////////////////////////////////////////////////////////////////
#include <boost/smart_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Headers-GUI
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Config.h"

namespace gaia
{
class BaseWidget;

namespace properties
{
///////////////////////////////////////////////////////////////////////////////
/// /brief Base class for properties.
///
/// Properties enable to modify the behaviour of the widget. They are specially
/// designed to be applied when reading a file (for example, XML layout file).
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL Property
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param name : Property name.
	///////////////////////////////////////////////////////////////////////////
	Property(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Destructor
	///////////////////////////////////////////////////////////////////////////
	virtual ~Property(void) {}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the name of the property.
	///
	/// \return The name of the property.
	///////////////////////////////////////////////////////////////////////////
	const std::string& getName() const {return myName;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the value of the property under a string form.
	///
	/// \param name : Name of the desired property.
	///
	/// \return A string corresponding to the value of the property. 
	///////////////////////////////////////////////////////////////////////////
	virtual std::string getProperty(const std::string& name);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Applies the property to the widget.
	///
	/// \param target : The widget we want to apply the property.
	/// \param value : A string describing the action to set. 
	///////////////////////////////////////////////////////////////////////////
	virtual void setProperty(BaseWidget& target, const std::string& value) = 0; 

protected:
	///Property name
	std::string myName;
};

///Properties are mainly handled through smart ptr. So here is a useful typedef.
typedef boost::shared_ptr<Property> PtrProperty;

} //end namespace properties

} //end namespace

#endif