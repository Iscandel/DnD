#include "SideDefManager.h"

#include "tools/FileReading.h"

SideDefManager::SideDefManager()
{
}


SideDefManager::~SideDefManager()
{
}

const SideDef& SideDefManager::getDef(const std::string& typeId)
{
	DefMap::iterator it = myMap.find(typeId);
	if (it == myMap.end())
	{
		std::string msg = "Side def manager : resource" +
			tools::numToString(typeId) + "not defined";
		ILogger::log(ILogger::ERRORS) << msg << "\n";
		throw std::runtime_error(msg);
	}

	return it->second;

}

SideDefManager::DefMap::iterator SideDefManager::getIterator()
{
	myCurrentIt = myMap.begin();
	return myCurrentIt;
}

bool SideDefManager::hasNext()
{
	auto tmp = myCurrentIt;
	++tmp;
	return (tmp != myMap.end());
}

SideDefManager::DefMap::iterator SideDefManager::next()
{
	return ++myCurrentIt;
}

void SideDefManager::load(const std::string& fileName)
{
	TextFile file(fileName);

	int nbElements = 0, imageId;
	std::string typeId;

	file >> nbElements;

	for (int i = 0; i < nbElements; i++)
	{
		file >> typeId >> imageId;
		SideDef def(imageId);

		myMap[typeId] = def;
	}
}