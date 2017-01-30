#ifndef H__SFMLGRAPHICS__100620111958__H
#define H__SFMLGRAPHICS__100620111958__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLConfig.h"
#include "Gaia/BaseGraphics.h"

#include <SFML/Graphics.hpp>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief SFML implementation of the graphics class.
///////////////////////////////////////////////////////////////////////////////
class GAIA_SFML_DLL SFMLGraphics : public gaia::BaseGraphics
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param window : Pointer to the existing SFML RenderWindow.
	///////////////////////////////////////////////////////////////////////////
	SFMLGraphics(sf::RenderWindow* window = NULL);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawImage method.
	///
	/// \param image : Image to draw.
	///
	/// \param x : X left top coordinate.
	///
	/// \param y : Y left top coordinate.
	///
	/// \param width : It can be different from image own width, this results in a
	/// resize.
	///
	/// \param width : It can be different from image own height, this results in a
	/// resize.
	///////////////////////////////////////////////////////////////////////////
	void drawImage_impl(Image& image, int x, int y, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawLine method.
	///
	/// \param c1 : Top left corner.
	/// \param c2 : Bottom right corner.
	/// \param col : Line color.
	/// \param thickness : Thickness of the line.
	///////////////////////////////////////////////////////////////////////////
	void drawLine_impl(const Point& c1, 
					   const Point& c2, 
					   const Color& col, 
					   float thickness = 1.f);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawRectangle method
	///
	/// \param topLeft : Top left corner.
	/// \param width :Rectangle width.
	/// \param height : Rectangle height.
	/// \param col : Rectangle color.
	///////////////////////////////////////////////////////////////////////////
	void drawRectangle_impl(const Point& topLeft, 
							int width, 
							int height, 
							const Color& col, 
							int outlineThickness = 0,
							const Color& outlineColor = Color::Black);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new clipping area to the stack.
	///
	/// \param rect : clipping area.
	///////////////////////////////////////////////////////////////////////////
	void pushClippingArea(const gaia::IntRect& rect);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes the last clipping area (which is on top of the stack).
	///////////////////////////////////////////////////////////////////////////
	void popClippingArea();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the underlying RenderTarget.
	///
	/// \return The SFML RenderTarget.
	///////////////////////////////////////////////////////////////////////////
	sf::RenderTarget* getWindow() {return myWindow;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts a GUI rect to a SFML rect.
	///
	/// \param rect : Gui rectangle to convert.
	///
	/// \return An equivalent SFML rectangle.
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	sf::Rect<T> toSFMLRect(const IntRect& rect)
	{
		sf::Rect<T> res;
		res.left = (T)rect.x;
		res.top = (T)rect.y;
		
		res.width = (T)rect.width;
		res.height = (T)rect.height;

		return res;
	}

	void smoothImages(bool smooth);

	void drawOptimized();

	//@override
	void onWindowSizeAssigned();

	//@override
	void optimizeDrawing(bool opti);

	//@override
	void beginDraw();

	//@override
	//void endDraw();

	//void beginDraw() { myCacheImage.Clear(sf::Color(0,0,0,0));}

protected:
	sf::RenderTarget* myWindow;
	sf::RenderTexture myCacheImage;
	sf::RenderWindow* myRenderWindow;
};

} //end namespace

#endif