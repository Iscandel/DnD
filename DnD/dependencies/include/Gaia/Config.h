#ifndef H__CONFIG_030920110115__H
#define H__CONFIG_030920110115__H

#ifdef _MSC_VER

	#pragma warning(disable : 4251)

#endif

#if (defined(WIN32) || defined(__WIN32__) || defined(_WIN32)) && !defined(GAIA_STATIC)
	#if defined(GAIA_EXPORT)

		#define GAIA_DLL __declspec(dllexport)

	#else

		#define GAIA_DLL __declspec(dllimport)

	#endif
#else

	#define GAIA_DLL

#endif

#endif //End guards