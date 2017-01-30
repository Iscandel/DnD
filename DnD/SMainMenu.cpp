#include "SMainMenu.h"

#include "GraphicEngine.h"
#include "MainMenuView.h"
#include "SConnectionMenu.h"
#include "SMainMenuSolo.h"
#include "SoundEngine.h"


SMainMenu::SMainMenu()
{
}


SMainMenu::~SMainMenu()
{
}

void SMainMenu::init()
{
	setView(View::ptr(new MainMenuView));
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiMainMenu.xml");

	gaia::GuiManager* manager = gaia::GuiManager::getInstance();

	manager->getWidget<gaia::Button>("soloButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicSolo, this));
	manager->getWidget<gaia::Button>("multiButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicMulti, this));

	getSoundEngine()->playMusic("./data/music/intro.wav");

}

bool SMainMenu::catchEvent(const sf::Event& ev)
{
	gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));
	//if (ev.type == sf::Event::KeyPressed)
	//{
	//	//setClientGameState(GameState::ptr(new SMainMenu));
	//}

	return true;
}

void SMainMenu::update()
{
	processQueue();

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SMainMenu::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	default:
		break;
	}
}

void SMainMenu::onClicSolo(gaia::MouseEvent& ev)
{
	setClientGameState(GameState::ptr(new SMainMenuSolo));
}

void SMainMenu::onClicMulti(gaia::MouseEvent& ev)
{
	setClientGameState(GameState::ptr(new SConnectionMenu));
}