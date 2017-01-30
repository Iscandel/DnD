#ifndef H__XMLCONFIG_300920110028__H
#define H__XMLCONFIG_300920110028__H

#ifdef _MSC_VER

	#pragma warning(disable : 4251)

#endif

#if (defined(WIN32) || defined(__WIN32__) || defined(_WIN32)) && !defined(GAIA_XML_STATIC)
	#if defined(GAIA_XML_EXPORT)

		#define GAIA_XML_DLL __declspec(dllexport)

	#else

		#define GAIA_XML_DLL __declspec(dllimport)
	
	#endif
#else

	#define GAIA_XML_DLL

#endif

#endif //End guards