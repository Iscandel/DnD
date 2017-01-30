#include "SLobbyServer.h"

#include "GameEngine.h"
#include "NetworkEngine.h"
#include "SLobby.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"

SLobbyServer::SLobbyServer()
{
}


SLobbyServer::~SLobbyServer()
{
}

void SLobbyServer::init()
{
	getNetworkEngine()->listen(8205);
	getGameEngine()->setClientGameState(GameState::ptr(new SLobby));

	gaia::GuiManager::getInstance()->getWidget<gaia::Button>("startButton")->setVisible(true);
	//gaia::GuiManager::getInstance()->clean();
	//gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiMainConnection.xml");

	//gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	//manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));

	//manager->getWidget<gaia::Button>("soloButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicSolo, this));
}

bool SLobbyServer::catchEvent(const sf::Event& ev)
{
	//Game& game = getGameEngine()->getGame();

	//gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));

	return false;
}

void SLobbyServer::update()
{
	processQueue();

	//gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SLobbyServer::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	default:
		break;
	}
}