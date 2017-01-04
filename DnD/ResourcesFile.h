#ifndef H__FICHIERRESSOURCES__H
#define H__FICHIERRESSOURCES__H

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "tools/Singleton.h"

struct sDATHeader
{
    char uniqueID[5]; /// Unique ID used to know if this file is a DAT File from this class
    char version[3]; /// Version of the DAT file format
    unsigned int nb_files; /// Number of files in the DAT file
};

struct sFileEntry
{
    char name[300]; /// Name of the data file
    long size; /// Size of the data file
    long offset; /// Offset, in the DAT file where the file is
};

///////////////////////////////////////////////////////////////////////////////
// Descriptif de fichier ressources
///////////////////////////////////////////////////////////////////////////////
struct FileDescription
{
	//Référence sur le fichier en question
	std::ifstream myFileHandle;
	//Header du fichier
	sDATHeader myHeader;
	//Liste des fichiers composant le fichier ressources
    std::vector<sFileEntry> myFileEntries;
	//Chemin du fichier ressources
	std::string myFilePath;
	//Identifiant du fichier ressource (plus court, plus simple)
	std::string myFileName;
};

class ResourcesFile : public Singleton<ResourcesFile>
{
public:
	ResourcesFile(void);
	~ResourcesFile(void);

public:
	typedef std::map<std::string, FileDescription*> MapResourceFiles;

public :
	///////////////////////////////////////////////////////////////////////////
	// Crée un fichier de ressources.
	// Param : fichiers -> La liste des chemins des fichiers à ajouter au dat
	//		   destination -> Le chemin du dat
	//		   IdFichiers -> Paramètre facultatif afin de pouvoir récupérer les
	//						 nom de fichiers dans le dat via ce paramètre plutôt
	//						 que par leur chemin complet. IdFichiers doit être 
	//						 de la même taille que fichiers.
	///////////////////////////////////////////////////////////////////////////
	bool create (const std::vector<std::string>& files,
				const std::string& destination, 
				const std::vector<std::string> fileIds = std::vector<std::string>());

	///////////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////////
    void read (const std::string& source, const std::string& identifiant);

	///////////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////////
    char* getFile (const std::string& fileName, const std::string& datId, long int* taille = NULL);

	///////////////////////////////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////////////////////////////
    long int getFileLength (const std::string& fileName, const std::string& datId);
private :
    //std::string m_datfile; /// name of the DAT file
    //sDATHeader m_header; /// file header
   // std::vector<sFileEntry> m_entries; /// vector of files entries

	std::map<std::string, FileDescription*> myResourceFiles;


};

#endif
