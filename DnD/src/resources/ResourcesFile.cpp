#include "ResourcesFile.h"
#include "tools/Logger.h"

ResourcesFile::ResourcesFile(void)
{
}

ResourcesFile::~ResourcesFile(void)
{
	MapResourceFiles::iterator it = myResourceFiles.begin();
	for(; it != myResourceFiles.end(); ++it)
	{
		it->second->myFileHandle.close();
		delete it->second;
	}
}

////////////////////////////////////////////////////////////////////////////
bool ResourcesFile::create(const std::vector<std::string>& files,
							  const std::string &destination,
							  const std::vector<std::string> filesId)
{
    //An input file stream to read each file included
    std::ifstream file;
    //An output file stream to write our DAT file
    std::ofstream datfile;
    //The buffer used to read/write the DAT file
    char buffer[1];
	sDATHeader header;
	std::vector<sFileEntry> entries;
 
    //DATHeader
    //We start by filling it with 0
    memset (&header, 0, sizeof(header));
    //Then we copy the ID
    memcpy (header.uniqueID, "MONDAT", 5);
    //Then the version
    memcpy (header.version, "1.0", 3);
    //Then the number of files to include
    header.nb_files = (unsigned int)files.size();
 
    //Next, we open each file in order to create the File Entries Table
    for (unsigned int i = 0; i< files.size(); i++)
    {
		//An file entry in order to push it in the object's std::vector
		sFileEntry entry;

        file.open (files[i].c_str(), std::ifstream::in | std::ifstream::binary);
        if (file.is_open())
        {
            //Filling the FileEntry with 0
            memset (&entry, 0, sizeof(sFileEntry) );

			if(filesId.size() != 0)
			{
				//We keep the file name
				memcpy (entry.name, filesId[i].c_str(), strlen ( filesId[i].c_str() ) );
			}
			else
			{
				//We keep the file name
				memcpy (entry.name, files[i].c_str(), strlen ( files[i].c_str() ) );
			}

            //We calculate its size
            file.seekg (0, std::ios::end);
            entry.size = file.tellg();
            //Since we don't know exactly its final position in the DAT file, let's use 0
            entry.offset = 0;
            //We finished with this file
            file.close();
 
            //Finally, we add this File Entry in our std::vector
            entries.push_back(entry);
        }
        else
        {
            //Simple error track
			ILogger::log(ILogger::ERRORS) << "File "<< files[i] << " leaded to an error.\n";
            return (false);
        }
    }
 
    //Now, we know everything about our files, we can update offsets
    long actual_offset = 0;
    actual_offset += sizeof(sDATHeader);
    actual_offset += header.nb_files * sizeof(sFileEntry);
    for (unsigned int i=0;i< entries.size();i++)
    {
        entries[i].offset = actual_offset;
        actual_offset += entries[i].size;
    }
 
    //And finally, we are writing the DAT file
    datfile.open (destination.c_str(), std::ofstream::out | std::ofstream::binary);
 
    //First, we write the header
    datfile.write ((char*)&header, sizeof(sDATHeader) );
 
    //Then, the File Entries Table
    for (unsigned int i=0;i < entries.size();i++)
    {
        datfile.write ((char*)&entries[i], sizeof(sFileEntry) );
    }
 
    //Finally, we write each file
    for (unsigned int i = 0; i< entries.size(); i++)
    {
		file.open (files[i].c_str(), std::ifstream::in | std::ifstream::binary);
        if (file.is_open())
        {
            file.seekg (0, std::ios::beg);
            while (file.read (buffer, 1))
            {
                datfile.write (buffer, 1);
            }
            file.close();
        }
		else
		{
			throw std::runtime_error("File " + files[i] + " not found.\n");
		}
        file.clear();
    }
    //And it's finished
    datfile.close();
    return (true);
}

void ResourcesFile::read (const std::string& source, const std::string& identifiant)
{

	if(myResourceFiles.find(identifiant) != myResourceFiles.end())
		throw std::runtime_error("Resource file " + identifiant + " already registered\n");

	//MesFichiersRessources.insert(std::make_pair(identifiant, DescriptifFichier()));

	//Crée en même temps l'entrée dans la map
	myResourceFiles[identifiant] = new FileDescription;
	FileDescription& desc = *myResourceFiles[identifiant];
	desc.myFileName = identifiant;

    //The input file stream from which we want informations
    //std::ifstream datfile;
    //A file entry in order to push it in the object's std::vector
    sFileEntry entry;
 
    //Filling the header with 0
    memset (&desc.myHeader, 0, sizeof(desc.myHeader));
    //We open the DAT file to read it
    desc.myFileHandle.open(source.c_str(), std::ifstream::in | std::ifstream::binary);
    if (desc.myFileHandle.is_open())
    {
        //Getting to the Header position
        desc.myFileHandle.seekg (0, std::ios::beg);
        //Reading the DAT Header
		desc.myFileHandle.read ((char*)&desc.myHeader, sizeof(sDATHeader));
        //Next we are reading each file entry
        for (unsigned int i=0;i<desc.myHeader.nb_files;i++)
        {
            //Reading a File Entry
            desc.myFileHandle.read ((char*)&entry, sizeof(sFileEntry));
            //Pushing it in our std::vector
			desc.myFileEntries.push_back(entry);
        }
        //Since all seems ok, we keep the DAT file name
		desc.myFilePath = source;
    }
	else
	{
		throw std::runtime_error("File " + source + " couldn't be opened.");
	}
    //Closing the DAT file
    //datfile.close();
}

char* ResourcesFile::getFile (const std::string& fileName, const std::string& datId, long int* size)
{
    //The input file stream from which we want information
    //std::ifstream datfile;
    //The buffer used to read/write the DAT file
    char* buffer;

	MapResourceFiles::iterator it = myResourceFiles.find(datId);
	if(it == myResourceFiles.end())
	{
		ILogger::log(ILogger::ERRORS) << "File " << datId << " not found.\n";
		throw std::runtime_error("File " + datId + " not found.\n");
	}
	FileDescription& desc = *(it->second);
 
    //First, we have to find the file needed
    for (unsigned int i = 0; i< desc.myHeader.nb_files; i++)
    {
        //If we found it
        if (desc.myFileEntries[i].name == fileName)
        {
            //We are allocating memory to the buffer
            buffer = new char[(desc.myFileEntries[i].size)];

			if(size != NULL)
				*size = desc.myFileEntries[i].size;

            //Opening the DAT file ot read the file datas needed
            //datfile.open (m_datfile.c_str(), std::ifstream::in | std::ifstream::binary);
            if (desc.myFileHandle.is_open())
            {
                //Going to the right position
                desc.myFileHandle.seekg (desc.myFileEntries[i].offset, std::ios::beg);
                //Reading
                desc.myFileHandle.read (buffer, desc.myFileEntries[i].size);
                //We can close the DAT file
                //desc.monHandleFichier.close();
                //Returning the buffer
                //WARNING WARNING WARNING
                //Since we are allocating the buffer, user must delete it himself
                //WARNING WARNING WARNING
                return buffer;
            }
        }
    }
    //Finally, there is no such file in our DAT file
    return NULL;
}

long int ResourcesFile::getFileLength (const std::string& fileName, const std::string& datId)
{
	MapResourceFiles::iterator it = myResourceFiles.find(datId);
	if(it == myResourceFiles.end())
	{
		ILogger::log(ILogger::ERRORS) << "File "<< datId << " not found.\n";
		throw std::runtime_error("File " + datId + " not found.\n");
	}
	FileDescription& desc = *(it->second);

    //First, we have to find the file needed
    for (unsigned int i = 0; i < desc.myHeader.nb_files; i++)
    {
        //If we found it
        if (desc.myFileEntries[i].name == fileName)
        {
            //Returning the size of the file found
            return (desc.myFileEntries[i].size);
        }
    }
    return 0;
}
