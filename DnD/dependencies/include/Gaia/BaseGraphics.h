#ifndef H__BASEGRAPHICS__100620110033__H
#define H__BASEGRAPHICS__100620110033__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Config.h"
#include "Gaia/tools/NonCopyable.h"
#include "Gaia/Rectangle.h"
#include "Gaia/Point.h"
#include "Gaia/Color.h"
#include "Gaia/Image.h"
#include "Gaia/BaseFont.h"
#include "Gaia/VisualString.h"

#include <stack>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Base class for graphics.
///
/// Provides pure virtual base functions for rendering.
///////////////////////////////////////////////////////////////////////////////
	class GAIA_DLL BaseGraphics : public NonCopyable
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor.
	///////////////////////////////////////////////////////////////////////////////
	BaseGraphics(void);
	
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Virtual destructor.
	///////////////////////////////////////////////////////////////////////////////
	virtual ~BaseGraphics(void) {}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws an image on the window.
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
	///
	/// \see drawImage_impl
	///////////////////////////////////////////////////////////////////////////////
	void drawImage(Image& image, int x, int y, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws a line on the window.
	///
	/// \param c1 : Top left corner.
	/// \param c2 : Bottom right corner.
	/// \param col : Line color.
	/// \param thickness : Thickness of the line.
	///
	/// \see drawLine_impl
	///////////////////////////////////////////////////////////////////////////////
	void drawLine(const Point& c1, const Point& c2, const Color& col, float thickness = 1.f);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws a filled rectangle on the window.
	///
	/// \param topLeft : Top left corner.
	/// \param bottomRight : Bottom right corner.
	/// \param col : Rectangle color.
	///
	/// \see drawRectangle_impl
	///////////////////////////////////////////////////////////////////////////////
	void drawRectangle(const Point& topLeft, 
					   const Point& bottomRight,
					   const Color& col,
					   int outlineThickness = 0,
					   const Color& outlineColor = Color::Black);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws a filled rectangle on the window.
	///
	/// \param topLeft : Top left corner.
	/// \param width :Rectangle width.
	/// \param height : Rectangle height.
	/// \param col : Rectangle color.
	///
	/// \see drawRectangle_impl
	///////////////////////////////////////////////////////////////////////////////
	void drawRectangle(const Point& topLeft, 
					   int width, 
					   int height, 
					   const Color& col,
					   int outlineThickness = 0,
					   const Color& outlineColor = Color::Black);
	
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws text.
	///
	/// \param string : Informations about the string rendering.
	/// \param text : The string to draw.
	/// \param x : X coordinate.
	/// \param y : Y coordinate.
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawText(VisualString& string, const std::string& text, int x, int y);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws text.
	///
	/// \param font : The font to use.
	/// \param text : The string to draw.
	/// \param x : X coordinate.
	/// \param y : Y coordinate.
	/// \param col : Text color.
	/// \param height : Character height.
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawText(PtrFont font, 
						  const std::string& text, 
						  int x, 
						  int y, 
						  const Color& col, 
						  unsigned int height);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new clipping area to the stack.
	///
	/// \param rect : clipping area.
	///////////////////////////////////////////////////////////////////////////////
	virtual void pushClippingArea(const IntRect& rect); //push / pop ??

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Removes the last clipping area (which is on top of the stack).
	///////////////////////////////////////////////////////////////////////////////
	virtual void popClippingArea();

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Sets the window size.
	///
	/// \param width : Window width.
	/// \param height :Window height.
	///////////////////////////////////////////////////////////////////////////////
	void assignWindowSize(int width, int height);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Sets the global font.
	///
	/// \param font : The font to set.
	///
	/// \see BaseFont::setDefaultFont
	///////////////////////////////////////////////////////////////////////////////
	void setGlobalFont(PtrFont font);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the global font.
	///
	/// \return font : The global font.
	///////////////////////////////////////////////////////////////////////////////
	PtrFont getGlobalFont() {return myGlobalFont;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Sets the origin used for all drawings. By default, origin is fixed
	/// to (0,0).
	///
	/// \param x : X coordinate.
	/// \param y : Y Coordinate.
	///////////////////////////////////////////////////////////////////////////////
	void setOrigin(int x, int y);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns origin of the coordinate system.
	///
	/// \return A point defining the current origin.
	///////////////////////////////////////////////////////////////////////////////
	const Point& getOrigin() const {return myOrigin;}
	
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Moves the current origin with the X and Y values given.
	///
	/// \param x : X value to add to the current X value.
	/// \param y : Y value to add to the current Y value.
	///////////////////////////////////////////////////////////////////////////////
	void translate(int x, int y);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Defines whether we should optimize the rendering (if supported).
	///
	/// \param opti : true to optimize, false to deactivate optimization.
	///////////////////////////////////////////////////////////////////////////////
	virtual void optimizeDrawing(bool opti) {myOptimizeDrawing = opti;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns whether the rendering is set to be optimized
	///
	/// \return : true if optimized, false otherwise
	///////////////////////////////////////////////////////////////////////////////
	bool isOptimizedDrawing()const {return myOptimizeDrawing;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Processes the optimized drawing. Needs to be redefined by inherited
	///		   classes.
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawOptimized();

	void invalidate() {myInvalidate = true;}

	bool isInvalidated() const {return myInvalidate;}

	virtual void beginDraw() {}

	virtual void endDraw() {myInvalidate = false;}

	virtual void onWindowSizeAssigned() {}

protected:
	///////////////////////////////////////////////////////////////////////////////
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
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawImage_impl(Image& image, int x, int y, int width = 0, int height = 0) = 0;

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawLine method.
	///
	/// \param c1 : Top left corner.
	/// \param c2 : Bottom right corner.
	/// \param col : Line color.
	/// \param thickness : Thickness of the line.
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawLine_impl(const Point& c1, const Point& c2, const Color& co, float thickness = 1.f) = 0;

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawRectangle method
	///
	/// \param topLeft : Top left corner.
	/// \param width :Rectangle width.
	/// \param height : Rectangle height.
	/// \param col : Rectangle color.
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawRectangle_impl(const Point& hautGauche, 
									int largeur, 
									int hauteur, 
									const Color& coul, 
									int outlineThickness,
									const Color& outlineColor) = 0;

protected:
	//public:
	IntRect myWindowSize; ///< Window size.
	IntRect myCurrentSize; ///< Current clipping area.
	std::stack<IntRect> myOldSizes; ///<Stack of clipping areas.
	PtrFont myGlobalFont; ///<  Global font.
	Point myOrigin; ///< Origin point of the coordinate system.
	bool myOptimizeDrawing; ///< Defines whether we should optimize rendering.
	bool myInvalidate;
	//Image myCacheImage;
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline void BaseGraphics::drawImage(Image& image, int x, int y, int width, int height)
{
	drawImage_impl(image, myOrigin.x + x, myOrigin.y + y, width, height);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline void BaseGraphics::drawLine(const Point& c1, const Point& c2, const Color& col, float thickness)
{
	drawLine_impl(myOrigin + c1, myOrigin + c2, col, thickness);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline void BaseGraphics::drawRectangle(const Point& topLeft, 
									    int width, 
										int height, 
										const Color& col, 
										int outlineThickness,
									    const Color& outlineColor)
{
	drawRectangle_impl(myOrigin + topLeft, width, height, col, outlineThickness, outlineColor);
}

} //end namespace

#endif