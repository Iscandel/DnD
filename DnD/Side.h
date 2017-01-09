#pragma once

#include "tools/WithSmartPtr.h"
#include "Action.h"
#include "Entity.h"
#include "ResourceImage.h"

#include <iostream>
#include <vector>

class Side : public WithSmartPtr<Side>, public GraphicEntity
{
public:
	enum SideType {
		VOID,
		WALL,
		DOOR
	};

public:
	typedef std::map<std::string, ResourceImage::ptr> ResourceImagesMap;

public:
	Side();
	~Side();

	///sets revealed status to True.
	void revealSide() { myIsRevealed = true;}

	void setAction(Action::ptr action) { myAction = action; }

	//void onPassTrough(Player::ptr player) { myAction.action(player); }	
	
	///returns side's status
	bool isRevealed() {return myIsRevealed;}
	
	void setType(SideType type) { myType = type; }

	SideType getType() const { return myType; }

	virtual void update(const Game&, unsigned int) {}

	std::vector<Image>& getCurrentImages() { return myCurrentImages; } //ou std::vector. Retourner éventuellement l'objet Image

	void addResourceImage(const std::string& idName, ResourceImage::ptr res)
	{
		myImages[idName] = res;
	}

	void removeResourceImage(const std::string& idName)
	{
	}

	void addCurrentDrawnImage(const std::string& name, int num = 0)
	{
		ResourceImagesMap::iterator it = myImages.find(name);
		if (it != myImages.end())
		{
			myCurrentImages.push_back(it->second->getImage(num));
		}
	}

	void setCurrentDrawnImage(const std::string& name, int num = 0)
	{
		myCurrentImages.clear();
		addCurrentDrawnImage(name, num);
	}

	friend std::ostream& operator <<(std::ostream& os, const Side& maze)
	{
		if (maze.getType() == WALL)
			os << "#";
		else if (maze.getType() == VOID)
			os << ".";
		else
			os << "\"";

		return os;
	}
private:
	///Side's status
	bool myIsRevealed;

	Action::ptr myAction;

	SideType myType;

	ResourceImagesMap myImages;
	//PtrResourceImage myCurrentImage;
	std::vector<Image> myCurrentImages;
};

