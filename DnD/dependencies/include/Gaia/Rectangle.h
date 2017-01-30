#ifndef H__RECTANGLE_050920112202__H
#define H__RECTANGLE_050920112202__H

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Represents a rectangular area. The T template parameter enables to
/// use integer and decimal values.
///////////////////////////////////////////////////////////////////////////////
template<class T>
struct Rect
{
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///////////////////////////////////////////////////////////////////////////////
	Rect()
	:x(0)
	,y(0)
	,width(0)
	,height(0)
	{}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	/// 
	/// \param x : x component top left.
	/// \param y : y component top left.
	/// \param width : Width of the rectangle
	/// \param height : Height of the rectangle.
	///////////////////////////////////////////////////////////////////////////////
	Rect(T x, T y, T width, T height)
	:x(x)
	,y(y)
	,width(width)
	,height(height)
	{
	}

	bool contains(T x, T y) const
	{
		return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
	}

	T x; ///< x coordinate of the top left corner.
	T y; ///< y coordinate of the top left corner.
	T width; ///< width of the rectangle.
	T height; ///< height of the rectangle.
};

/// \brief Typedef for a rectangle handling integer positions.
typedef Rect<int> IntRect;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline bool operator == (const Rect<int>& left, const Rect<int>& right)
{
	return (left.x == right.x && 
			left.y == right.y && 
			left.width == left.width && 
			left.height == right.height);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
inline bool operator != (const Rect<int>& left, const Rect<int>& right)
{
	return !(left == right);
}

};

#endif