#include "CellDefManager.h"

#include "tools/FileReading.h"

CellDefManager::CellDefManager()
{
}


CellDefManager::~CellDefManager()
{
}

const CellDef& CellDefManager::getDef(int typeId)
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

CellDefManager::DefMap::iterator CellDefManager::getIterator()
{
	myCurrentIt = myMap.begin();
	return myCurrentIt;
}

bool CellDefManager::hasNext()
{
	auto tmp = myCurrentIt;
	++tmp;
	return (tmp != myMap.end());
}

CellDefManager::DefMap::iterator CellDefManager::next()
{
	return ++myCurrentIt;
}

void CellDefManager::load(const std::string& fileName)
{
	TextFile file(fileName);

	int nbElements = 0, imageId, typeId;

	file >> nbElements;

	for(int i = 0; i < nbElements; i++)
	{
		file >> typeId >> imageId;
		CellDef def(imageId);
		
		myMap[typeId] = def;
	}
}