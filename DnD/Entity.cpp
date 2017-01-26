#include "Entity.h"

#include "tools/Tools.h"


Entity::Entity(int id)
:myId(id)
,myToDestroy(false)
,myHasLost(false)
{
}


Entity::~Entity(void)
{
}

GraphicEntity::GraphicEntity(int id)
:Entity(id)
,myIsSelectable(true)
,myIsSelected(false)
,myIsHoverable(true)
,myRotation(0.f)
//,myOrigin(0.f, 0.f)
{
}

Rect<double> GraphicEntity::getBoundingRect(int windowSizeX, int windowSizeY)
{
	throw std::runtime_error("Not implemented");
	//Local coordinate system
	//Rect<double> boundingRect(0. - myOrigin.x * windowSizeX, //A vérif
	//						  0. - myOrigin.y * windowSizeY, 
	//						  getRelSizeX() * windowSizeX, 
	//						  getRelSizeY() * windowSizeY);

	//double rotation = getRotation();
	//if(std::abs(rotation) > 0.00001)
	//{
	//	std::vector<Point<double> > relGraphicPosition;
	//	relGraphicPosition.push_back(tools::applyRotation(Point<double>(boundingRect.x, boundingRect.y), rotation));
	//	relGraphicPosition.push_back(tools::applyRotation(Point<double>(boundingRect.x +  boundingRect.width, boundingRect.y), rotation));
	//	relGraphicPosition.push_back(tools::applyRotation(Point<double>(boundingRect.x, boundingRect.y + boundingRect.height), rotation));
	//	relGraphicPosition.push_back(tools::applyRotation(Point<double>(boundingRect.x + boundingRect.width, boundingRect.y + boundingRect.height), rotation));

	//	Point<double> topLeft(relGraphicPosition[0]);
	//	Point<double> downRight(relGraphicPosition[0]);
	//	for(unsigned int i = 0; i < relGraphicPosition.size(); i++)
	//	{
	//		if(relGraphicPosition[i].x < topLeft.x)
	//			topLeft.x = relGraphicPosition[i].x;
	//		if(relGraphicPosition[i].y < topLeft.y)
	//			topLeft.y = relGraphicPosition[i].y;
	//		if(relGraphicPosition[i].x > downRight.x)
	//			downRight.x = relGraphicPosition[i].x;
	//		if(relGraphicPosition[i].y > downRight.y)
	//			downRight.y = relGraphicPosition[i].y;			
	//	}
	//	boundingRect.x = topLeft.x;
	//	boundingRect.y = topLeft.y;
	//	boundingRect.width = downRight.x - topLeft.x;
	//	boundingRect.height = downRight.y - topLeft.y;
	//}
	//if(boundingRect.x) boundingRect.x /= (double) windowSizeX;
	//if(boundingRect.y) boundingRect.y /= (double) windowSizeY;
	//boundingRect.width /= (double)windowSizeX;
	//boundingRect.height /= (double) windowSizeY;

	//boundingRect.x += getX() + myOrigin.x;
	//boundingRect.y += getY() + myOrigin.y;
	//return boundingRect;
}

