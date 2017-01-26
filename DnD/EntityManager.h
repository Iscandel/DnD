#ifndef H__ENTITYMANAGER_260120150121__H
#define H__ENTITYMANAGER_260120150121__H

#include "Dragoon.h"
#include "Player.h"
#include "Treasure.h"

class EntityManager
{
//public:
//	typedef std::map<int, Entity::ptr> EntityMap;
//	typedef std::map<int, Player::ptr> PlayerMap;

public:
	void registerPlayer(Player::ptr entity)
	{
		myEntities[entity->getId()] = entity;
		myPlayers[entity->getId()] = entity;
	}

	void registerDragoon(Dragoon::ptr dragoon)
	{
		myEntities[dragoon->getId()] = dragoon;
		myDragoon = dragoon;
	}

	void registerTreasure(Treasure::ptr treasure)
	{
		myEntities[treasure->getId()] = treasure;
		myTreasure = treasure;
	}

	Entity::ptr removeEntity(int id)
	{
		Entity::ptr removed;
		std::map<int, Entity::ptr>::iterator it = myEntities.find(id);
		if (it != myEntities.end())
			removed = it->second;

		myEntities.erase(id);
		myPlayers.erase(id);

		return removed;		
	}

	void update();

	//std::vector<PtrGraphicEntity> getEntities() {return myEntities;}

	//Player::ptr getPlayer();
	Entity::ptr getEntity(int id);
	Player::ptr getPlayer(int id);

	std::vector<Entity::ptr> getEntities();
	std::vector<Player::ptr> getPlayers();
	Dragoon::ptr getDragoon();
	Treasure::ptr getTreasure();
	//std::vector<Player::ptr> getEntities() {return myEntities;}

	//Dragoon::ptr getDragoon() { return mDragoon; }


	//std::vector<PtrGraphicEntity> getHoveredEntities(const Point<double>& relPos)
	//{
	//	std::vector<PtrGraphicEntity> res;
	//	for(unsigned int i = 0; i < myEntities.size(); i++)
	//	{
	//		Point<double> pos(myEntities[i]->getX(), myEntities[i]->getY());
	//		Point<double> size(myEntities[i]->getRelSizeX(), myEntities[i]->getRelSizeY());

	//		double rotation = myEntities[i]->getRotation();
	//		if(std::abs(rotation) > 0.00001)
	//		{
	//			std::vector<Point<double> > relGraphicPosition;
	//			relGraphicPosition.push_back(tools::applyRotation(pos, rotation));
	//			relGraphicPosition.push_back(tools::applyRotation(Point<double>(pos.x +  size.x, pos.y), rotation));
	//			relGraphicPosition.push_back(tools::applyRotation(Point<double>(pos.x, pos.y + size.y), rotation));
	//			relGraphicPosition.push_back(tools::applyRotation(Point<double>(pos.x + size.x, pos.y + size.y), rotation));

	//			Point<double> topLeft(relGraphicPosition[0]);
	//			Point<double> downRight(relGraphicPosition[0]);
	//			for(unsigned int i = 0; i < relGraphicPosition.size(); i++)
	//			{
	//				if(relGraphicPosition[i].x < topLeft.x)
	//					topLeft.x = relGraphicPosition[i].x;
	//				if(relGraphicPosition[i].y < topLeft.y)
	//					topLeft.y = relGraphicPosition[i].y;
	//				if(relGraphicPosition[i].x > downRight.x)
	//					downRight.x = relGraphicPosition[i].x;
	//				if(relGraphicPosition[i].y > downRight.y)
	//					downRight.y = relGraphicPosition[i].y;

	//				pos = topLeft;
	//				size.x = downRight.x - topLeft.x;
	//				size.y = downRight.y - topLeft.y;
	//			}

	//		}

	//		if(relPos.x >= pos.x &&
	//		   relPos.y >= pos.y &&
	//		   relPos.x <= pos.x + size.x && 
	//		   relPos.y <= pos.y + size.y)
	//		{
	//			res.push_back(myEntities[i]);
	//		}
	//	}
	//	return res;
	//}



	int createNewId();

	//EntityMap myEntities;
	std::map<int, Entity::ptr> myEntities;
	std::map<int, Player::ptr> myPlayers;
	std::map<int, Entity::ptr> myLostEntities;

	Dragoon::ptr myDragoon;
	Treasure::ptr myTreasure;
	//std::vector<PtrGraphicEntity> myEntities;
};

#endif
