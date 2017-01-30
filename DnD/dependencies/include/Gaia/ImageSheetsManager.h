#ifndef H__IMAGESHEETSMANAGER_100920111328__H
#define H__IMAGESHEETSMANAGER_100920111328__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/ImageSheet.h"
#include "Gaia/tools/Singleton.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Manager for all image sheets which are part of a same graphic theme.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL ImageSheetsManager : public gaia::Singleton<ImageSheetsManager>
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Registers the given image sheet in the manager.
	///
	/// \param is : Pointer to the image sheet to register. It must have been
	/// dynamically allocated.
	///////////////////////////////////////////////////////////////////////////////
	void registerImageSheet(ImageSheet* is);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns a pointer to the requested image.
	///
	/// \param sheet : Name of the image sheet on which the requested image is.
	/// \param name : Name of the image.
	///
	/// \return A pointer to the image
	///////////////////////////////////////////////////////////////////////////////
	Image* getImage(const std::string& sheet, const std::string& name) 
	{
		if(myImageSheets.find(sheet) != myImageSheets.end())
			return myImageSheets[sheet]->getImage(name);
		
		return NULL;
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Resets the manager removing all imageSheets.
	///////////////////////////////////////////////////////////////////////////
	void clearImages();

protected:
	std::map<std::string, boost::shared_ptr<ImageSheet> > myImageSheets; ///< Image sheets list.
};

} //end namespace

#endif