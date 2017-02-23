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
	//Game& game = getGameEngine()->getGame();

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
		std::string reason;
		if (!MessageBuilder::extractSvConnectionResult(msg, result, error, reason))
			return;

		if (result == 1)
		{
			setClientGameState(GameState::ptr(new SLobby));
		}
		else
		{
			gaia::GuiManager* manager = gaia::GuiManager::getInstance();
			manager->getWidget<gaia::Label>("errorLabel")->setText(reason);
			//manager->getWidget<gaia::Label>("errorLabel")->setTextColor(gaia::Color(255, 0, 0));
		}

	}
	break;

	default:
		break;
	}
}

void SConnectionMenu::onClicConnection(gaia::MouseEvent& ev)
{
	gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	
	Message msg = MessageBuilder::connection(
		manager->getWidget<gaia::TextBox>("ipField")->getText(),
		manager->getWidget<gaia::TextBox>("pseudoField")->getText());
	sendMessageToNetwork(msg);
	//getNetworkEngine()->connection();
}

void SConnectionMenu::onClicHost(gaia::MouseEvent& ev)
{
	gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	std::string nick = manager->getWidget<gaia::TextBox>("pseudoField")->getText();

	if(nick == "")
		manager->getWidget<gaia::Label>("errorLabel")->setText("Nick ?");
	else
	{
		Game& game = getGameEngine()->getGame();
		game.setup1PGame(nick);
		setServerGameState(GameState::ptr(new SLobbyServer));
	}
}