#ifndef H__GUITOOLS_050920110002__H
#define H__GUITOOLS_050920110002__H

#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "Gaia/Config.h"

namespace gaia
{
namespace tools
{
const double PI = 3.14159265358979323846;

///////////////////////////////////////////////////////////////////////////
/// Converts a number into a string. If the conversion fails, the result
/// will be an empty string.
///
/// \param val: value to convert
///
/// \return A string representation of the value
///////////////////////////////////////////////////////////////////////////
template<class T>
std::string numToString(const T& val)
{
	//Create an output stream
	std::ostringstream oss;
	// write a number
	oss << val;
	// get the string
	return oss.str();
}

///////////////////////////////////////////////////////////////////////////
/// Converts a number into a wide string. If the conversion fails, the result
/// will be an empty string.
///
/// \param val: value to convert
///
/// \return A wide string representation of the value
///////////////////////////////////////////////////////////////////////////
template<class T>
std::wstring numToWString(const T& num)
{
	// create an output stream
	std::wostringstream oss;
	// write a number in the stream
	oss << num;
	// get the string
	return oss.str();
}

///////////////////////////////////////////////////////////////////////////
/// Converts a string into a number. If the conversion fails, the result
/// could take any value.
///
/// \param val: value to convert
///
/// \return A string representation of the value
///////////////////////////////////////////////////////////////////////////
template<class T>
T stringToNum(const std::string& chaine)
{
	std::istringstream iss( chaine );
	T nombre;
	iss >> nombre; 
	return nombre;
}

///////////////////////////////////////////////////////////////////////////
/// Converts a string into a number. If the conversion fails, the function
/// returns false, else, it returns true.
///
/// \param val: value to convert
/// \param res: A reference to the converted string into number
///
/// \return true if the conversion is succesful, false if not.
///////////////////////////////////////////////////////////////////////////
template<class T>
bool sec_stringToNum(const std::string& string, T& res)
{
	// créer un flux à partir de la chaîne à convertir
	std::istringstream iss(string);
	return iss >> res != 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief converts a string into a boolean.Returns false if the string cannot
/// be interpreted as true.
///
/// \param value : string to convert.
///
/// \return The string equivalent as a boolean.
///////////////////////////////////////////////////////////////////////////////
GAIA_DLL bool stringToBool(const std::string& value);

///////////////////////////////////////////////////////////////////////////
/// \brief Converts a string into wide string.
///
/// \param s: string to convert
///
/// \return the wide string corresponding
///////////////////////////////////////////////////////////////////////////
GAIA_DLL std::wstring stringToWString(const std::string& s);

///////////////////////////////////////////////////////////////////////////
/// Returns the closest integer to the value.
///
/// \param value: value to test.
///
/// \return The closest integer to the value.
///////////////////////////////////////////////////////////////////////////
template<class T>
int closestInt(T value)
{
	return static_cast<int>(value + 0.5);
}


///////////////////////////////////////////////////////////////////////////
/// Splits the given string using the given string separator.
///
/// \param s: String to split.
/// \param separator: the separator used
///
/// \return A vector containing the splitted string
///////////////////////////////////////////////////////////////////////////
GAIA_DLL std::vector<std::string> split(const std::string& s, const std::string& separator);

namespace color
{
	///////////////////////////////////////////////////////////////////////////
	/// Converts a color given by a 32 bits representation into the red, green,
	/// blue components (0 -> 255)
	///
	/// \param argb: The int color.
	///	\param r: The returned red component
	///	\param g: The returned green component
	///	\param b: The returned blue component
	///////////////////////////////////////////////////////////////////////////
	GAIA_DLL void intToARGB(int argb, int& r, int& g, int& b, int& a);

	///////////////////////////////////////////////////////////////////////////
	/// Converts a HSB color to a RGB color.
	///
	/// \param f: H component (between 0.f and 1.f)
	/// \param f1: S component (between 0.f and 1.f)
	/// \param f2: B component (between 0.f and 1.f)
	///
	/// \return The corresponding RGB color (ARGB 32 bits format)
	///////////////////////////////////////////////////////////////////////////
	GAIA_DLL int HSBtoRGB(float f, float f1, float f2);

	///////////////////////////////////////////////////////////////////////////
	/// Converts a HSB color to a RGB color.
	///
	/// \param h: H component
	/// \param s: S component
	/// \param b: B component
	///
	/// \return The corresponding RGB color (ARGB 32 bits format)
	///////////////////////////////////////////////////////////////////////////
	GAIA_DLL int HSBtoRGB(int h, int s, int b);

} //end color namespace

} //end tools namespace

} // end namespace

#endif