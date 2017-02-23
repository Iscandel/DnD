#ifndef H__PROGRESSBARSIMPLERENDERER_110920111614__H
#define H__PROGRESSBARSIMPLERENDERER_110920111614__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/WidgetRenderer.h"
#include "Gaia/widgets/ProgressBar.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Shape renderer for progress bars.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ProgressBarSimpleRenderer :
	public gaia::TplWidgetRenderer<ProgressBar>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param w : The widgets set to the renderer. Must be a ProgressBar 
	/// class, or inherited.
	///////////////////////////////////////////////////////////////////////////
	ProgressBarSimpleRenderer(PtrWidget w = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget.  
	///
	/// \param Gfx : Pointer to the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	void draw_impl(BaseGraphics* Gfx);

protected:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the background.  
	///
	/// \param Gfx : Pointer to the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	void drawBackground(BaseGraphics* Gfx);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the bar, which depends on the progression value.  
	///
	/// \param Gfx : Pointer to the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	void drawBar(BaseGraphics* Gfx);

protected:
	Color myBackgroundColor;
	Color myBarColor;
};

}

#endif