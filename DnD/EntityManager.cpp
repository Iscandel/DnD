#include "EntityManager.h"


void EntityManager::update()
{
	std::map<int, Entity::ptr>::iterator it = myEntities.begin();
	for(it; it != myEntities.end();)
	{
		if (it->second->mustBeDestroyed())
		{
			myPlayers.erase(it->first);
			it = myEntities.erase(it);
		}
		else if (it->second->hasLost())
		{
			myLostEntities[it->first] = it->second;
			myPlayers.erase(it->first);
			it = myEntities.erase(it);
		}
		else
			++it;
	}
}

int EntityManager::createNewId()
{
	static int id = 1;

	return id++;
}

std::vector<Entity::ptr> EntityManager::getEntities()
{
	std::vector<Entity::ptr> res;

	std::map<int, Entity::ptr>::iterator it = myEntities.begin();
	for (it; it != myEntities.end(); ++it)
	{
		res.push_back(it->second);
	}

	return res;
}

std::vector<Player::ptr> EntityManager::getPlayers()
{
	std::vector<Player::ptr> res;

	std::map<int, Player::ptr>::iterator it = myPlayers.begin();
	for (it; it != myPlayers.end(); ++it)
	{
		res.push_back(it->second);
	}

	return res;
}

Dragoon::ptr EntityManager::getDragoon()
{
	return myDragoon;
}

Treasure::ptr EntityManager::getTreasure()
{
	return myTreasure;
}

Entity::ptr EntityManager::getEntity(int id) 
{
	std::map<int, Entity::ptr>::iterator it = myEntities.find(id);
	if(it != myEntities.end())
		return it->second; 

	return Entity::ptr();
}

Player::ptr EntityManager::getPlayer(int id) 
{
	std::map<int, Player::ptr>::iterator it = myPlayers.find(id);
	if (it != myPlayers.end())
		return it->second;

	return Player::ptr();
}

void EntityManager::clear()
{
	myEntities.clear();
	myPlayers.clear();
	myLostEntities.clear();
}

//Player::ptr EntityManager::getPlayer(int id)
//{
//	EntityMap::iterator it = myEntities.find(id);
//	if (it != myEntities.end())
//		return std::dynamic_pointer_cast<Player>(it->second);
//	return Player::ptr();
//}
//
//Entity::ptr EntityManager:: getEntity(int id)
//{
//	return myEntities[id]; 
//}