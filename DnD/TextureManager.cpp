#include "TextureManager.h"
#include "tools/FileReading.h"
#include "tools/Logger.h"
#include "ResourcesFile.h"

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
}

//void ElementSkinsManager::th_chargement(void* v)
//{
//	PtrElementSkin* Tmp = reinterpret_cast<PtrElementSkin*>(v);
//	PtrElementSkin Data = *Tmp;
//	Data->recharger();
//}

///////////////////////////////////////////////////////////////////////////////
// Charge la ressource id
///////////////////////////////////////////////////////////////////////////////
TextureManager::PtrResource TextureManager::loadResource(int id)
{
	MapResources::iterator it = myResources.find(id);
	if(it == myResources.end())
		throw std::runtime_error("ResourceImage " + tools::numToString(id) + " should already exist.");

	//MonThread.push_back(boost::shared_ptr<sf::Thread>());
	//MonThread.back().reset(new sf::Thread(&ElementSkinsManager::th_chargement, &it->second));//&MesRessources[it->first]));
	//MonThread.back()->Launch();
	it->second->reload(true);

	return it->second;
}

///////////////////////////////////////////////////////////////////////////////
// Libère la ressource id si seul le manager l'utilise
///////////////////////////////////////////////////////////////////////////////
void TextureManager::freeResource(int id)
{
	MapResources::iterator it = myResources.find(id);
	if(it == myResources.end())
		throw std::runtime_error("ResourceImage " + tools::numToString(id) + " should already exist.");

	if(it->second.unique())
	{
		it->second->free();
	}

}
///////////////////////////////////////////////////////////////////////////////
// Libere toutes les ressources qui sont uniquement utilisées par 
// le manager
///////////////////////////////////////////////////////////////////////////////
void TextureManager::freeResources()
{
	MapResources::iterator it = myResources.begin();
	for(; it != myResources.end(); ++it)
	{
		if(it->second.unique())
		{
			it->second->free();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Précharge toutes les ressources utilisables par le manager : Offsets,
// et couleur de transparence
///////////////////////////////////////////////////////////////////////////////
bool TextureManager::preload()
{
	TextFile file("./data/resourceTextures.dat");
	if (!file.isOpen())
	{
		ILogger::log(ILogger::ERRORS) << "Impossible de trouver le fichier d'images TexturesDat.dat";
		return false;
	}

	int nbElements;

	//nbLotsElementsSkin = Fichier.getArgument<int>();
	file >> nbElements;

	int num = 0;
	while(num < nbElements)
	{
		int id;
		std::string path;
		//L'ID
		file >> id;
		file >> path;
		myResources[id].reset(new ResourceTexture);
		myResources[id]->setTexturePath(path);

		num++;	
	}
	return true;
}