#pragma once

#include "Side.h"
#include "game/Direction.h"
#include "entity/Entity.h"
#include "factory/ObjectFactoryManager.h"
#include "resources/ResourceImage.h"
#include "tools/WithSmartPtr.h"

class Cell : public WithSmartPtr<Cell>, public GraphicEntity
{
public:
	using ptr = WithSmartPtr<Cell>::ptr;

//public:
//	typedef std::map<std::string, ResourceImage::ptr> ResourceImagesMap;

public:
	/**
	* Constructor without arguments.
	* All sides are set to Void.
	*/
	Cell();

	/**
	* Constructor with arguments.
	* @param east
	* @param north
	* @param west
	* @param south
	*/
	Cell(const Point<int>& coords, Side::ptr east, Side::ptr north, Side::ptr west, Side::ptr south);

	/**
	*
	* @param direction
	* @return the corresponding side
	*/
	Side::ptr getSide(Direction direction);

	void setSide(Direction direction, Side::ptr side);

	virtual void update(GameState&, const Game&, unsigned int) override {}

	//void addResourceImage(const std::string& idName, ResourceImage::ptr res);// {myImages.insert(std::make_pair(idName, res));}// = res;}
	//																	   //void setImageBack(PtrResourceImage res) {myImageBack = res;}
	////PtrResourceImage getCurrentImage() {return myCurrentImage;} //ou std::vector. Retourner éventuellement l'objet Image
	//std::vector<Image>& getCurrentImages() { return myCurrentImages; } //ou std::vector. Retourner éventuellement l'objet Image

	//void addCurrentDrawnImage(const std::string& name, int num = 0);
	//void setCurrentDrawnImage(const std::string& name, int num = 0);

	//const Point<int>& getCoords() const { return myCoords; }

protected:
	//Point<int> myCoords;

	//public boolean visitee = false;
	/**
	* The east side.
	*/
	Side::ptr myEastSide;

	/**
	* The north side.
	*/
	Side::ptr myNorthSide;

	/**
	* The west side.
	*/
	Side::ptr myWestSide;

	/**
	* The south side.
	*/
	Side::ptr mySouthSide;

	//ResourceImagesMap myImages;
	////PtrResourceImage myCurrentImage;
	//std::vector<Image> myCurrentImages;
};

