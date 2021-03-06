#ifndef H__TOOLS_230520152033__H
#define H__TOOLS_230520152033__H

#include "Array2D.h"
#include "Color.h"

#include <algorithm>
#include <string>

namespace tools
{
	const double PI = 3.14159265358979323846;
	const double INV_PI = 0.3183098861837906715377;
	const double MAX_DOUBLE = 10e9;
	const double EPSILON = 1e-4;

	inline double toRadian(double degres)
	{
		return (degres * tools::PI) / 180.;
	}

	inline double toDegre(double radian)
	{
		return (radian * 180. ) / tools::PI;
	}

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
T stringToNum(const std::string& string)
{
	std::istringstream iss(string);
	T number;
	iss >> number; 
	return number;
}

///////////////////////////////////////////////////////////////////////////
/// Converts a string into a boolean. If the conversion fails, the result
/// could take any value.
///
/// \param val: value to convert
///
/// \return A string representation of the value
///////////////////////////////////////////////////////////////////////////
template<>
inline bool stringToNum(const std::string& string)
{
	std::string sCopy = string;
	std::transform(sCopy.begin(), sCopy.end(), sCopy.begin(), ::tolower);
	if (string == "1" || sCopy == "true")
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////
/// Converts a string into a color. If the conversion fails, the result
/// could take any value.
///
/// \param string: value to convert
///
/// \return A string representation of the value
///////////////////////////////////////////////////////////////////////////
template<class T>
Color stringToColor(const std::string& string)
{
	std::istringstream iss(string);
	T x, y, z;
	iss >> x >> y >> z;

	Color col(x, y, z);
	return col;
}

template<class T>
T thresholding(T val, T min, T max)
{
	return val < min ? min : val  > max ? max : val;
}

template<class T>
int sign(T val)
{
	if (val >= (T)0)
		return 1;
	return -1;
}

template<class T>
inline double interp1(double advance, T start, T end)
{
	return (1 - advance) * start + advance * end;
}

///////////////////////////////////////////////////////////////////////////
/// \brief Basic random function. Requires that the seed was initialized 
/// before
///
/// \param min : min random value
///
/// \param max : max value included (?)
///
/// \return a random value between [min, max]
///////////////////////////////////////////////////////////////////////////
inline double random(double min, double max) 
{
	return (rand() / (double) RAND_MAX) * (max - min) + min;
}

inline std::string getExtension(const std::string& s)
{
	size_t index = s.find_last_of('.');
	if (index != std::string::npos)
	{
		return s.substr(index);
	}

	return "";
}

}

#endif