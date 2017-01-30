#include "SLobby.h"

#include "GameEngine.h"
#include "MainMenuView.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

SLobby::SLobby()
{
}


SLobby::~SLobby()
{
}

void SLobby::init()
{
	setView(View::ptr(new MainMenuView));
	gaia::GuiManager::getInstance()->clean();
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiLobby.xml");


	gaia::GuiManager::getInstance()->getWidget<gaia::Button>("startButton")->setVisible(false);
	//gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	//manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));

	//manager->getWidget<gaia::Button>("soloButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicSolo, this));
}

bool SLobby::catchEvent(const sf::Event& ev)
{
	//Game& game = getGameEngine()->getGame();

	//gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));

	return false;
}

void SLobby::update()
{
	processQueue();

	//gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SLobby::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	//case SV_GAME_INFO:
	//{
	//	Game& game = getGameEngine()->getGame();
	//	int id = msg.iData[Message::Key::SvGameInfo::YOUR_ID];
	//	game.addLocalId(id);

	//	//Infos sur les autres joueurs
	//}
	//break;

	default:
		break;
	}
}