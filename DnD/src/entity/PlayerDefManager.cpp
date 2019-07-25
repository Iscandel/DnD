#include "PlayerDefManager.h"

#include "tools/FileReading.h"

PlayerDefManager::PlayerDefManager()
{
}


PlayerDefManager::~PlayerDefManager()
{
}

const PlayerDef& PlayerDefManager::getDef(int typeId)
{
	DefMap::iterator it = myMap.find(typeId);
	if (it == myMap.end())
	{
		std::string msg = "Cell def manager : resource" +
			tools::numToString(typeId) + "not defined";
		ILogger::log(ILogger::ERRORS) << msg << "\n";
		throw std::runtime_error(msg);
	}

	return it->second;

}

PlayerDefManager::DefMap::iterator PlayerDefManager::getIterator()
{
	myCurrentIt = myMap.begin();
	return myCurrentIt;
}

bool PlayerDefManager::hasNext()
{
	auto tmp = myCurrentIt;
	++tmp;
	return (tmp != myMap.end());
}

PlayerDefManager::DefMap::iterator PlayerDefManager::next()
{
	return ++myCurrentIt;
}

void PlayerDefManager::load(const std::string& fileName)
{
	TextFile file(fileName);

	int nbElements = 0, imageId, typeId;

	file >> nbElements;

	for (int i = 0; i < nbElements; i++)
	{
		file >> typeId >> imageId;
		PlayerDef def(imageId);

		myMap[typeId] = def;
	}
}