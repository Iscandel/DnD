#ifndef H__PROPERTYSYSTEM_070920110127__H
#define H__PROPERTYSYSTEM_070920110127__H

#include <string>
#include <map>
#include <vector>

#include "Gaia/Property.h"

namespace gaia
{
class BaseWidget;

///////////////////////////////////////////////////////////////////////////////
/// \brief Stores widgets properties, arranged by type of widget. 
///
/// This class also provides functions to register, delete, and apply a property.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL PropertySystem
{
public:
	typedef std::map<std::string, properties::PtrProperty> PropertyMap;
	typedef std::map<std::string, PropertyMap> PropertyMultimap;

	///////////////////////////////////////////////////////////////////////////
	// Constructeur
	///////////////////////////////////////////////////////////////////////////
	PropertySystem(void);

	///////////////////////////////////////////////////////////////////////////
	// Destructeur
	///////////////////////////////////////////////////////////////////////////
	~PropertySystem(void);

	///////////////////////////////////////////////////////////////////////////
	/// Registers a property in the manager.
	///
	/// \param type : String type of the widget for which the property is
	/// intended.
	///
	/// \param p : The property to register.
	///////////////////////////////////////////////////////////////////////////
	void addProperty(const std::string& type, properties::PtrProperty p);

	///////////////////////////////////////////////////////////////////////////
	/// Deletes a property.
	///
	/// \param type : String type of the widget for which the property is
	/// intended.
	///
	/// \param name : Name of the property.
	///////////////////////////////////////////////////////////////////////////
	bool deleteProperty(const std::string& type, const std::string& nom);

	///////////////////////////////////////////////////////////////////////////
	/// Checks whether the property exists.
	///
	/// \param type : String type of the widget for which the property is
	/// intended.
	///
	/// \param name : Name of the property to check.
	///
	/// \return true if it exists, false if it cannot be found.
	///////////////////////////////////////////////////////////////////////////
	bool exists(const std::string& type, const std::string& nom);

	///////////////////////////////////////////////////////////////////////////
	/// Applies the property to the widget, using the given string.
	///
	/// \param type : String type of the widget for which the property is
	/// intended.
	///
	/// \param target : The widget for which the property applies.
	///
	/// \param name : Name of the desired property.
	///
	/// \param value : String value of the property.
	///////////////////////////////////////////////////////////////////////////
	void setProperty(const std::string& type, 
					 BaseWidget& target, 
					 const std::string& name, 
					 const std::string& value);

	///////////////////////////////////////////////////////////////////////////
	/// Returns a string representing the value of the property.
	/// 
	/// \param type : String type of the widget for which the property is
	/// intended.
	///
	/// \param name : Name of the property.
	///
	/// \return A string value of the property.
	///////////////////////////////////////////////////////////////////////////
	std::string getProperty(const std::string& type, const std::string& nom);

	///////////////////////////////////////////////////////////////////////////
	/// Returns all the the properties belonging to a particular widget type.
	/// 
	/// \param type : String type of the widget
	///
	/// \return A vector containing smart pointers on properties.
	///////////////////////////////////////////////////////////////////////////
	std::vector<properties::PtrProperty> getProperties(const std::string& type);

protected:
	//Liste des propriétés possédées par le widget
	PropertyMultimap myProperties;
};

};

#endif