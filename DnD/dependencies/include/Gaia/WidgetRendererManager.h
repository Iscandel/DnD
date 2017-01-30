#ifndef H__WIDGETRENDERERMANAGER_100920111345__H
#define H__WIDGETRENDERERMANAGER_100920111345__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/WidgetRenderer.h"
#include "Gaia/widgets/BaseWidget.h"
#include "Gaia/tools/Singleton.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// Base class for widget renderer factory.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL WidgetRendererFactory
{
public:
	virtual IWidgetRenderer* create(PtrWidget widget) = 0;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Enables to create a widget renderer factory associated to a renderer
/// type.
///
/// Usage : 
///
/// \code
/// PtrWidgetRendererFactory wrf(new TplWidgetRendererFactory<SomeRenderer>);
/// \endcode
///////////////////////////////////////////////////////////////////////////////
template<class T>
class TplWidgetRendererFactory : public WidgetRendererFactory
{
public:
///////////////////////////////////////////////////////////////////////////////
/// \brief Creates a new widget renderer
///
/// \param widget : Targeted widget by the renderer.
///
/// \return A pointer to the newly created widget renderer.
///////////////////////////////////////////////////////////////////////////////
IWidgetRenderer* create(PtrWidget widget)
{
	return new T(widget);
}

};

/// \brief Practical typedef.
typedef boost::shared_ptr<WidgetRendererFactory> PtrWidgetRendererFactory;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
/// \brief Manager for widget renderers.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL WidgetRendererManager :
	public gaia::Singleton<WidgetRendererManager>
{
public:
	/// \brief Practical typedef.
	typedef std::map<std::string, PtrWidgetRendererFactory> RendererList;

public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Uses the widget renderer factory to create the associated 
	/// renderer.
	///
	/// If the factory is not found, an exception is thrown.
	///
	/// \param rendererName : Associated name of the renderer.
	/// \param widget : widget associated to the renderer. It can't be a 
	/// null pointer.
	///////////////////////////////////////////////////////////////////////////
	IWidgetRenderer* createRenderer(const std::string& rendererName, PtrWidget widget);

	///////////////////////////////////////////////////////////////////////////
	/// \brief adds a new widget renderer factory to the manager.
	///
	/// \param rendererName : Name to give to the renderer.
	/// \param factory : The factory that will create the renderer.
	///////////////////////////////////////////////////////////////////////////
	void addWidgetRenderer(const std::string& rendererName, PtrWidgetRendererFactory factory);

protected:
	RendererList myRenderers; ///< Renderer list.
};

};

#endif