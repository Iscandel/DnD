///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Color.h"

Color::Color(int r, int g, int b, int a)
:r(r)
,g(g)
,b(b)
,a(a)
{

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color::Color(float r, float g, float b, float a)
:r(static_cast<int>(r * 255))
,g(static_cast<int>(g * 255))
,b(static_cast<int>(b * 255))
,a(static_cast<int>(a * 255))
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color::Color(int argb)
{
	a = (argb >> 24) & 0xFF;
	r = (argb >> 16) & 0xFF;
	g = (argb >> 8 ) & 0xFF;
	b = (argb      ) & 0xFF;
}

bool operator == (const Color& c1, const Color& c2)
{
	return (c1.a == c2.a && c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

bool operator != (const Color& c1, const Color& c2)
{
	return !(c1 == c2);
}

Color operator + (const Color& c1, const Color& c2)
{
	Color res;
	res.a = c1.a + c2.a;
	res.r = c1.r + c2.r;
	res.g = c1.g + c2.g;
	res.b = c1.b + c2.b;

	return res;
}

Color& operator += (Color& c1, const Color& c2)
{
	return c1 = c1 + c2;
}

Color operator * (const Color& c1, const Color& c2)
{
	Color res;
	res.a = static_cast<int>((c1.a / 255.f) * (c2.a / 255.f));
	res.r = static_cast<int>((c1.r / 255.f) * (c2.r / 255.f));
	res.g = static_cast<int>((c1.g / 255.f) * (c2.g / 255.f));
	res.b = static_cast<int>((c1.b / 255.f) * (c2.b / 255.f));

	return res;
}

Color& operator *= (Color& c1, const Color& c2)
{
	return c1 = c1 * c2;
}