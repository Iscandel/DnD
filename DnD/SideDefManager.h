#pragma once

#include "tools/Singleton.h"

#include <map>
#include <string>

class SideDef
{
public:
	SideDef() {}
	SideDef(int imageId) { this->imageId = imageId; }
	~SideDef() {}

	int imageId;
};

class SideDefManager : public Singleton<SideDefManager>
{
public:
	SideDefManager();
	~SideDefManager();

public:
	typedef std::map<std::string, SideDef> DefMap;
	typedef DefMap::iterator MapIterator;

public:

	const SideDef& getDef(const std::string& typeId);

	DefMap::iterator getIterator();

	bool hasNext();

	DefMap::iterator next();

	void load(const std::string& path);

	int getNumberElements() { return myMap.size(); }

protected:
	DefMap myMap;
	MapIterator myCurrentIt;
};