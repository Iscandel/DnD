#include "GraphicEngine.h"
#include "game/GameEngine.h"
#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

GraphicEngine::GraphicEngine(void)
:myElapsedTime(0)
{
	setWindowSize(Point<int>(1024, 768));
	myWindow.create(sf::VideoMode(getWindowSizeX(), getWindowSizeY()), "DnD");
	//myWindow.EnableVerticalSync(true);
	myWindow.setFramerateLimit(60);
	myWindow.setKeyRepeatEnabled(false);
	gaia::GuiManager::getInstance()->setWindowSize(getWindowSizeX(), getWindowSizeY());
	gaia::BaseGraphics* graphics = new gaia::SFMLGraphics(&myWindow);
	graphics->setGlobalFont(gaia::PtrFont(new gaia::SFMLFont("./data/fonts/arial.ttf")));
	gaia::GuiManager::getInstance()->setGraphics(graphics);
	gaia::GuiManager::getInstance()->enableKeyRepeat(true);
	gaia::xml::XMLWidgetLookLoader::loadImageSet("./data/gui/imagesWindowsTheme.xml");
	gaia::xml::XMLWidgetLookLoader::loadLooks("./data/gui/lookWindowsTheme.xml");
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
GraphicEngine::~GraphicEngine(void)
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GraphicEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GraphicEngine::update()
{
	processQueue();

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void GraphicEngine::draw()
{
	setElapsedTime(myClock.getElapsedTime().asMilliseconds());
	//std::cout << 1000. / getElapsedTime() << std::endl;
	myClock.restart();
	myWindow.clear(sf::Color::Black);
	getGameEngine()->draw();
	gaia::GuiManager::getInstance()->draw();

	myWindow.display();
}

void GraphicEngine::draw(const sf::Drawable& sp)
{
	myWindow.draw(sp);
}

void GraphicEngine::draw(PtrTexture texture, int x, int y, IntRect& rect, int scaleX, int scaleY, float rotation)
{
}