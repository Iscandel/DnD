#include "DraggableImage.h"



DraggableImage::DraggableImage(const std::string& name,
	int x,
	int y,
	int width,
	int height)
:gaia::ImageBox(name, x, y, width, height)
, myIsDragging(false)
{
}


DraggableImage::~DraggableImage()
{
}

bool DraggableImage::handleMousePressed_impl(gaia::MouseEvent& ev) 
{ 
	if (ev.getButton() == gaia::MouseButton::LEFT)
	{ 
		myIsDragging = true;
		myOffset.x = ev.getX();
		myOffset.y = ev.getY();
		moveToForeground();
		catchMouseInputs();
		ev.use(); 
		return true;
	}

	return false; 
}

bool DraggableImage::handleMouseReleased_impl(gaia::MouseEvent& ev) 
{ 
	if (myIsDragging)
	{
		releaseMouseInputs();
		myIsDragging = false;
		requestFocus(false);
	}

	ev.use();
	return true;;
}

bool DraggableImage::handleMouseHover_impl(gaia::MouseEvent& ev) 
{ 
	if (myIsDragging)
	{
		gaia::Point mouseScreen = convertToScreenCoordinates(gaia::Point(ev.getX(), ev.getY()));
		setPosition(mouseScreen.x - myOffset.x, mouseScreen.y - myOffset.y);
		//setPosition(ev.getX() - myOffset.x, ev.getY() - myOffset.y);
	}
	ev.use(); 
	return true; 
}

gaia::Point DraggableImage::convertToScreenCoordinates(const gaia::Point& pos)
{
	gaia::Point res = pos;
	res.x += getX();
	res.y += getY();

	gaia::BaseWidget* parent = getParent();

	while(parent != nullptr)
	{
		res.x += parent->getX();
		res.y += parent->getY();
		parent = parent->getParent();
	}
	
	return res;
}