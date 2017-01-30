#ifndef H__ADDPROPERTY_310820112321__H
#define H__ADDPROPERTY_310820112321__H

#include <string>

#include "Gaia/widgets/BaseWidget.h"

namespace gaia
{
	template<class T, class PROP>
	void addProperty(const std::string& name)
	{
		BaseWidget::addSharedProperty<T, PROP>(name);
	}

	template<class T, class PROP>
	void replaceProperty(const std::string& name)
	{
		BaseWidget::replaceSharedProperty<T, PROP>(name);
	}


	GAIA_DLL void addDefinedProperties();

}//end namespace

#endif