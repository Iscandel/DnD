#ifndef H__COLOR__311020132113__H
#define H__COLOR__311020132113__H


///////////////////////////////////////////////////////////////////////////////
/// Class enabling to manipulate ARGB colors.
///////////////////////////////////////////////////////////////////////////////
struct Color
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param r : red component (0 to 255)
	/// \param g : green component (0 to 255)
	/// \param b : blue component (0 to 255)
	/// \param a : alpha component (0 to 255)
	///////////////////////////////////////////////////////////////////////////////
	Color(int r = 0, int g = 0, int b = 0, int a = 255);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param r : red component (0.f to 1.f)
	/// \param g : green component (0.f to 1.f)
	/// \param b : blue component (0.f to 1.f)
	/// \param a : alpha component (0.f to 1.f)
	///////////////////////////////////////////////////////////////////////////////
	Color(float r, float g, float b, float a = 1.f);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param argb : 32 bits integer. The first 8 bits correspond to the alpha
	/// component, the next 8 bits to the red component, etc...
	///////////////////////////////////////////////////////////////////////////////
	Color(int argb);

	int r; ///< red component 
	int g; ///< green component
	int b; ///< blue component
	int a; ///< alpha component
};

bool operator == (const Color& c1, const Color& c2);

bool operator != (const Color& c1, const Color& c2);

Color operator + (const Color& c1, const Color& c2);

Color& operator += (Color& c1, const Color& c2);

Color operator * (const Color& c1, const Color& c2);

Color& operator *= (Color& c1, const Color& c2);

#endif