#ifndef H__GUISFMLTOOLS_180920111637__H
#define H__GUISFMLTOOLS_180920111637__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Color.h"

#include <SFML/Graphics.hpp>

namespace gaia
{
	namespace SFMLTools
	{
		///////////////////////////////////////////////////////////////////////////////
		/// \brief Converts an SFML color to a GUI color.
		///
		///	\return A GUI color equivalent to the sf::Color.
		///////////////////////////////////////////////////////////////////////////////
		inline Color toGuiColor(const sf::Color& col)
		{
			return Color(col.r, col.g, col.b, col.a);
		}

		///////////////////////////////////////////////////////////////////////////////
		/// \brief Converts an GUI color to an SFML color.
		///
		///	\return A SFML color equivalent to the  GUI color.
		///////////////////////////////////////////////////////////////////////////////
		inline sf::Color fromGuiColor(const Color& col)
		{
			return sf::Color(static_cast<sf::Uint8>(col.r), 
							 static_cast<sf::Uint8>(col.g), 
							 static_cast<sf::Uint8>(col.b), 
							 static_cast<sf::Uint8>(col.a));
		}
	}
}
#endif