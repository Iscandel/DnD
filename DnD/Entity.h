#pragma once

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "tools/Point.h"
#include "tools/Rectangle.h"
#include "tools/Tools.h"
//#include "DataImage.h"

//RessourceImage pour le dos des cartes
//RessourceImage pour la face
//class IEntityGraphic
//{
//protected:
//	std::map<std::string, PtrResourceImage > > myImages;
//};

class Game;

class Entity
{
public:
	Entity(int id);
	~Entity(void);

	virtual void update(const Game& game, unsigned int elapsed) = 0;

	void setToDestroy(bool destroy = true) {myToDestroy = destroy;}
	bool mustBeDestroyed() const {return myToDestroy;}

	int getId() const {return myId;}
	
protected:
	int myId;
	bool myToDestroy;
	//std::map<std::string, std::vector<DataImage<sf::Image> > > myImages;
};

//typedef boost::shared_ptr<Entity> PtrEntity;

class GraphicEntity : public Entity
{
public:
	GraphicEntity(int id);
	//virtual void draw() = 0;
	virtual void moveTo(double x, double y) {myDimensions.x = x; myDimensions.y = y;}

	void setPosition(const Point<double>& pos) {myDimensions.x = pos.x; myDimensions.y = pos.y;}

	void setRelSize(double width, double height) {myDimensions.width = width; myDimensions.height = height;}

	double getX() const {return myDimensions.x;}
	double getY() const {return myDimensions.y;}

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
	bool myIsSelectable;
	bool myIsSelected;
	bool myIsHoverable;

	float myRotation;
	Point<double> myOrigin;
};
typedef boost::shared_ptr<Entity> PtrEntity;
typedef boost::shared_ptr<GraphicEntity> PtrGraphicEntity;

