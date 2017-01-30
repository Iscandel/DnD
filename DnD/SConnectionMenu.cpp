#include "SConnectionMenu.h"

#include "GameEngine.h"
#include "GraphicEngine.h"
#include "MainMenuView.h"
#include "MessageBuilder.h"
#include "NetworkEngine.h"
#include "SLobby.h"
#include "SLobbyServer.h"

SConnectionMenu::SConnectionMenu()
{
}


SConnectionMenu::~SConnectionMenu()
{
}

void SConnectionMenu::init()
{
	setView(View::ptr(new MainMenuView));

	gaia::GuiManager::getInstance()->clean();
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiMainConnection.xml");

	gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	manager->getWidget<gaia::Button>("hostButton")->subscribeMouseReleased(gaia::my_bind(&SConnectionMenu::onClicHost, this));
	manager->getWidget<gaia::Button>("connectionButton")->subscribeMouseReleased(gaia::my_bind(&SConnectionMenu::onClicConnection, this));
}

bool SConnectionMenu::catchEvent(const sf::Event& ev)
{
	Game& game = getGameEngine()->getGame();

	gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));

	return false;
}

void SConnectionMenu::update()
{
	processQueue();

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SConnectionMenu::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::SV_CONNECTION_RESULT:
	{
		int result, error;
		if (!MessageBuilder::extractSvConnectionResult(msg, result, error))
			return;

		if (result == 1)
		{
			setClientGameState(GameState::ptr(new SLobby));
		}
		else
		{

		}

	}
	break;

	default:
		break;
	}
}

void SConnectionMenu::onClicConnection(gaia::MouseEvent& ev)
{
	getNetworkEngine()->connection();
}

void SConnectionMenu::onClicHost(gaia::MouseEvent& ev)
{
	setServerGameState(GameState::ptr(new SLobbyServer));
}