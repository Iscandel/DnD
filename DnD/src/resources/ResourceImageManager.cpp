#include "ResourceImageManager.h"
#include "tools/FileReading.h"
#include "tools/Logger.h"

ResourceImageManager::ResourceImageManager(void)
{
}

ResourceImageManager::~ResourceImageManager(void)
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
ResourceImageManager::PtrResource ResourceImageManager::loadResource(int id)
{
	MapResources::iterator it = myResources.find(id);
	if(it == myResources.end())
		throw std::runtime_error("ResourceImage " + tools::numToString(id) + " should already exist.");

	//MonThread.push_back(boost::shared_ptr<sf::Thread>());
	//MonThread.back().reset(new sf::Thread(&ElementSkinsManager::th_chargement, &it->second));//&MesRessources[it->first]));
	//MonThread.back()->Launch();
	it->second->reload();

	return it->second;
}

///////////////////////////////////////////////////////////////////////////////
// Libère la ressource id si seul le manager l'utilise
///////////////////////////////////////////////////////////////////////////////
void ResourceImageManager::freeResource(int id)
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
void ResourceImageManager::freeResources()
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
bool ResourceImageManager::preload()
{
	TextFile file("./data/resourceImages.dat");
	if (!file.isOpen())
	{
		ILogger::log(ILogger::ERRORS) << "Impossible de trouver le fichier d'images ResourceImages.dat";
		return false;
	}

	int nbElements;

	//nbLotsElementsSkin = Fichier.getArgument<int>();
	file >> nbElements;

	int num = 0;
	while(num < nbElements)
	{
		int id, textureId, x, y, width, height, isRect;

		//L'ID
		file >> id;
		myResources[id].reset(new ResourceImage);

		int nbIm = 0, nbImages;
		file >> nbImages;
		while(nbIm < nbImages)
		{
			file >> textureId >> isRect;
			if (isRect == 1)
				file >> x >> y >> width >> height;
			else
				x = y = width = height = -1;

			IntRect rect(x, y, width, height);

			Image image(textureId, rect);
			myResources[id]->add(image);

			nbIm++;
		}

		num++;	
	}
	return true;
}