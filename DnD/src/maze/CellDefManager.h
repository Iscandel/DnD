#pragma once

#include "tools/Singleton.h"

#include <map>

class CellDef
{
public:
	CellDef() {}
	CellDef(int imageId) { this->imageId = imageId; }
	~CellDef() {}

	int imageId;
};

class CellDefManager : public Singleton<CellDefManager>
{
public:
	CellDefManager();
	~CellDefManager();

public:
	typedef std::map<int, CellDef> DefMap;
	typedef DefMap::iterator MapIterator;

public:

	const CellDef& getDef(int typeId);

	DefMap::iterator getIterator();

	bool hasNext();

	DefMap::iterator next();

	void load(const std::string& path);

	int getNumberElements() { return (int) myMap.size(); }

protected:
	DefMap myMap;
	MapIterator myCurrentIt;
};

