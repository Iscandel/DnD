#ifndef H__LECTURE_FICHIER__H
#define H__LECTURE_FICHIER__H

#include <string>
#include <fstream>

#include "Policy.h"
#include "Logger.h"
#include "Point.h"


///////////////////////////////////////////////////////////////////////////////
// Final
///////////////////////////////////////////////////////////////////////////////

template<class U>
class FileBase
{
public:
	FileBase(const std::string& path = "")
	{
		U::open(myFile, path);
	}

	~FileBase()
	{
		myFile.close();
	}

	void open(const std::string& path)
	{
		if(myFile) 
			myFile.close(); 
		myFile.clear(); 
		U::open(myFile, path);
	}

	void close()
	{
		if(myFile)
			myFile.close();
	}

	bool isStreamError() {return myFile.fail();}

	bool eof() {return myFile.eof();}

	bool isOpen() const {return (myFile ? true : false);}

	template<class T>
	T getArgument()
	{
		return U::execute<T>(myFile);
	}

	template<class T>
	bool extractFromBuffer(T& value)
	{
		std::istringstream stream(myBuffer);
		return stream >> value != 0;

		if(!stream.eof())
			myBuffer = myBuffer.substr(stream.tellg(), myBuffer.size() - stream.tellg());
		else
			myBuffer = "";
	
	}

	template<class T>
	friend FileBase& operator >> (FileBase& b, T& value)
	{
		value = b.getArgument<T>();
		
		return b;
	}

	friend FileBase& operator >> (FileBase& base, Color& value)
	{
		int r, g, b;
		std::string sCol = base.getArgument<std::string>();
		std::istringstream stream(sCol);
		stream >> r >> g >> b;

		value = Color(r, g, b);

		if(stream.fail())
		{
			ILogger::log(ILogger::ERRORS) << LOGPOSITION << " Problem during extraction.\n";
		}
			
		return base;
	}

	friend FileBase& operator >> (FileBase& base, Point<int>& value)
	{
		//int x = base.getArgument<int>();
		//int y = base.getArgument<int>();

		//Valeur.x = x;
		//Valeur.y = y;
		//if(extraireFromBuffer(Valeur.x))
		//{
		//	extraireFromBuffer(Valeur.y);
		//}
		//else
		{
			std::string s = base.getArgument<std::string>();
			std::istringstream stream(s);
			stream >> value.x >> value.y;
			{
				//ILogger::log(ILogger::ERREURS) << POSITIONLOG << " Problème dans l'extraction\n";
			}

			if(!stream.eof())
			{
				base.myBuffer += s.substr(stream.tellg(), s.size() - stream.tellg());
			}
		}

		return base;
	}

protected:
	std::ifstream myFile;
	std::string myBuffer;
};

typedef FileBase<TextFilePolicy<ConvertPolicy> > TextFile;
typedef FileBase<BinaryFilePolicy> BinaryFile;



//class FichierTexte : public BaseFichier<PolitiqueFichierTexte<PolitiqueConversion> >
//{
//};
//
//class FichierBinaire : public BaseFichier<PolitiqueFichierBinaire>
//{
//};

#endif