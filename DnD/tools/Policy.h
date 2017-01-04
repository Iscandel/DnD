#ifndef H__POLITIQUE__H
#define H__POLITIQUE__H

#include <fstream>

#include "tools/Tools.h"

///////////////////////////////////////////////////////////////////////////////
// Une classe de politique qui effectue la conversion d'une chaine donn�e en
// entr�e en un type template T
///////////////////////////////////////////////////////////////////////////////
struct ConvertPolicy
{
	template<class T>
	static T convert(const std::string& c);
};

///////////////////////////////////////////////////////////////////////////////
// Simple conversion chaine -> nombre
///////////////////////////////////////////////////////////////////////////////
template<class T>
inline T ConvertPolicy::convert(const std::string& c)
{
	return tools::stringToNum<T>(c);
}

///////////////////////////////////////////////////////////////////////////////
// Sp�cialisation du template pour les std::string. Pas de conversion � faire
// puisqu'on a une std::string en entr�e
///////////////////////////////////////////////////////////////////////////////
template<>
inline std::string ConvertPolicy::convert(const std::string& c)
{
	return c;
}

///////////////////////////////////////////////////////////////////////////////
// Sp�cialisation pour les char*. Pointeur valide ?
///////////////////////////////////////////////////////////////////////////////
//template<>
//const char* PolitiqueConversion::convertir(const std::string& c)
//{
//	return c.c_str();
//}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classe de trait pour la r�cup�ration d'arguments issus de fichiers texte,
// �crits ligne par ligne, et # pour les commentaires
///////////////////////////////////////////////////////////////////////////////
template<class P>
class TextFilePolicy
{
public:
	///////////////////////////////////////////////////////////////////////////
	// R�cup�re un argument du fichier (int, string...)
	///////////////////////////////////////////////////////////////////////////
	template<class T>
	static T execute(std::ifstream& file);

	static void open(std::ifstream& file, const std::string& path)
	{
		file.open(path.c_str());
	}

protected:
	///////////////////////////////////////////////////////////////////////////
	// R�cup�re la premi�re chaine utile du fichier (apr�s zappage des
	// commentaires)
	///////////////////////////////////////////////////////////////////////////
	static std::string readString(std::ifstream& file)
	{
		std::string line = "";

		do
		{
			std::getline(file, line);
		}while (line[0] == '#');

		return line;
	}
};

template<class P>
template<class T>
inline T TextFilePolicy<P>::execute(std::ifstream& file)
{
	//Fait appel � une politique de conversion pour convertir le retour
	//de lireChaine()
	return P::convert<T>(readString(file));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classe de trait pour la r�cup�ration d'arguments issus de fichiers binaires,
///////////////////////////////////////////////////////////////////////////////
class BinaryFilePolicy
{
public:
	template<class T>
	static T execute(std::ifstream& file)
	{
		T string;
		fichier.read(reinterpret_cast<char*>(&string), sizeof(T));

		return string;
	}

	static void open(std::ifstream& file, const std::string& path)
	{
		file.open(path.c_str(), std::ios_base::binary);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Sp�cialisation pour les chaines de caract�res, dont la longueur doit �tre 
// lue avant
///////////////////////////////////////////////////////////////////////////////
template<>
inline std::string BinaryFilePolicy::execute(std::ifstream& file)
{
	sf::Int32 stringSize;
	file.read(reinterpret_cast<char*>(&stringSize), sizeof(sf::Int32));

	char* buffer = new char[stringSize + 1];
	buffer[stringSize] = '\0';

	file.read(buffer, stringSize);

	std::string res(buffer);
	delete buffer;

	return res;
}

#endif