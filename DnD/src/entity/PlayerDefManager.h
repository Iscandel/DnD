#pragma once

#include "tools/Singleton.h"

#include <map>

class DefPlayerManager
{
public:
	DefPlayerManager();
	~DefPlayerManager();
};



class PlayerDef
{
public:
	PlayerDef() {}
	PlayerDef(int imageId) { this->imageId = imageId; }
	~PlayerDef() {}

	int imageId;
};

class PlayerDefManager : public Singleton<PlayerDefManager>
{
public:
	PlayerDefManager();
	~PlayerDefManager();

public:
	typedef std::map<int, PlayerDef> DefMap;
	typedef DefMap::iterator MapIterator;

public:

	const PlayerDef& getDef(int typeId);

	DefMap::iterator getIterator();

	bool hasNext();

	DefMap::iterator next();

	void load(const std::string& path);

	int getNumberElements() { return (int)myMap.size(); }

protected:
	DefMap myMap;
	MapIterator myCurrentIt;
};
