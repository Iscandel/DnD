#ifndef H__ADDWIDGETRENDERERFACTORY_210620112125__H
#define H__ADDWIDGETRENDERERFACTORY_210620112125__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetRendererManager.h"

namespace gaia
{
	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a defined list of widgets renderers factories.
	///
	/// This function shouldn't be called by users. It is for internal use only.
	///////////////////////////////////////////////////////////////////////////
	GAIA_DLL void addDefinedWidgetRendererFactories();

	///////////////////////////////////////////////////////////////////////////
	/// \brief This function adds a new widget renderer factory identified by 
	/// its template name. 
	///
	/// So, the template parameter T should be a class derived from BaseWidget.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	void addWidgetRendererFactory(const std::string& factoryName)
	{
		PtrWidgetRendererFactory wrFactory(new TplWidgetRendererFactory<T>);
		WidgetRendererManager::getInstance()->addWidgetRenderer(factoryName, wrFactory);
	}
} //end namespace

#endif