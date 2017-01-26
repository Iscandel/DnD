#pragma once

#include <map>
#include <vector>

#include "EntityState.h"
#include "tools/Point.h"
#include "tools/Rectangle.h"
#include "tools/Tools.h"
#include "tools/WithSmartPtr.h"

//#include "DataImage.h"

//RessourceImage pour le dos des cartes
//RessourceImage pour la face
//class IEntityGraphic
//{
//protected:
//	std::map<std::string, PtrResourceImage > > myImages;
//};

class Game;
class GameState;
class SGameServer;
class Dragoon;
class Player;

class Entity : public WithSmartPtr<Entity>
{
public: 
	typedef std::shared_ptr<Entity> ptr;
public:
	Entity(int id);
	~Entity(void);

	virtual void update(GameState& state, const Game& game, unsigned int elapsed) = 0;

	void setToDestroy(bool destroy = true) {myToDestroy = destroy;}
	bool mustBeDestroyed() const {return myToDestroy;}

	virtual bool onMoved(SGameServer&) { return false; }
	virtual bool onArrivedOnCell(SGameServer&, Player&) { return false; }
	virtual bool onArrivedOnCell(SGameServer&, Dragoon&) { return false; }

	void setState(EntityState<Entity>::ptr state);

	int getId() const {return myId;}

	void defeat() { myHasLost = true; }
	bool hasLost() const { return myHasLost; }
	
protected:
	int myId;
	bool myToDestroy;

	bool myHasLost;
	//std::map<std::string, std::vector<DataImage<sf::Image> > > myImages;
};

//typedef boost::shared_ptr<Entity> PtrEntity;

class GraphicEntity : public Entity
{
public:
	GraphicEntity(int id);
	//virtual void draw() = 0;
	//virtual void moveTo(double x, double y) {myDimensions.x = x; myDimensions.y = y;}

	void setGraphicPosition(const Point<double>& pos) {myDimensions.x = pos.x; myDimensions.y = pos.y;}
	void setAbstractPosition(int x, int y) { myAbstractPos.x = x; myAbstractPos.y = y; }
	void setAbstractPosition(const Point<int>& pos) { myAbstractPos = pos; }

	void setRelSize(double width, double height) {myDimensions.width = width; myDimensions.height = height;}

	int getAbstractX() const {return myAbstractPos.x;}
	int getAbstractY() const {return myAbstractPos.y;}
	const Point<int> getAbstractPos() const { return myAbstractPos; }

	double getRelSizeX() const {return myDimensions.width;}
	double getRelSizeY() const {return myDimensions.height;}

	bool isSelectable() const {return myIsSelectable;}
	void setSelectable(bool selectable) {myIsSelectable = selectable;}

	bool isHoverable() const {return myIsHoverable;}
	void setHoverable(bool hoverable) {myIsHoverable = hoverable;}

	void setSelected(bool selected) {if(isSelectable()) myIsSelected = selected;}

	bool isSelected() const {return myIsSelected;}

	void setRotation(float rot) {myRotation = rot;}
	float getRotation() const {return myRotation;}

	void setOrigin(double origin) {myOrigin = origin;}
	Point<double> getOrigin() const {return myOrigin;}

	Rect<double> getBoundingRect(int windowSizeX, int windowSizeY);

protected:
	Rect<double> myDimensions;
	Point<int> myAbstractPos;
	bool myIsSelectable;
	bool myIsSelected;
	bool myIsHoverable;

	float myRotation;
	Point<double> myOrigin;
};


