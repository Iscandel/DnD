#ifndef H__WINDOWIMAGERENDERER_031120112356__H
#define H__WINDOWIMAGERENDERER_031120112356__H

#include "Gaia/widgetRenderers/WidgetRenderer.h"
#include "Gaia/widgets/Window.h"
#include "Gaia/tools/NonCopyable.h"

namespace gaia
{
class GAIA_DLL TitleBarImageRenderer : public gaia::TplWidgetRenderer<TitleBar>, public NonCopyable
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param w : The widgets set to the renderer. Must be a Label class, or
	/// inherited.
	///////////////////////////////////////////////////////////////////////////
	TitleBarImageRenderer(PtrWidget widget = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget.  
	///
	/// \param Gfx : Pointer the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	void draw_impl(BaseGraphics* Gfx);
};

class GAIA_DLL WindowImageRenderer :
	public gaia::TplWidgetRenderer<Window>
{
public:
	//struct PrivResizing
	//{
	//	enum pos
	//	{
	//		LEFT,
	//		TOP_LEFT,
	//		TOP,
	//		RIGHT,
	//		TOP_RIGHT,
	//		BOTTOM_RIGHT,
	//		BOTTOM,
	//		BOTTOM_LEFT,
	//		NONE
	//	};
	//};
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param w : The widgets set to the renderer. Must be a Label class, or
	/// inherited.
	///////////////////////////////////////////////////////////////////////////
	WindowImageRenderer(PtrWidget widget = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget.  
	///
	/// \param Gfx : Pointer the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	void draw_impl(BaseGraphics* Gfx);

	Window::PrivResizing::pos getEdge(int x, int y);

protected:
	const std::string myLeftEdge;
	const std::string myTopLeftEdge;
	const std::string myTopEdge;
	const std::string myTopRightEdge;
	const std::string myRightEdg;
	const std::string myBottomLeftEdge;
	const std::string myBottomEdge;
	const std::string myBottomRightEdge;
	const std::string myCenter;
};



} //end namespace 

#endif