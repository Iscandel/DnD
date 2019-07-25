#include "SLobby.h"

#include "game/GameEngine.h"
#include "graphic/GraphicEngine.h"
#include "graphic/MainMenuView.h"
#include "game/MessageBuilder.h"
#include "SGameBeginning.h"

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
	gaia::GuiManager::getInstance()->getWidget<gaia::TextBox>("sendBox")->subscribeKeyPressed(gaia::my_bind(&SLobby::onSendChatMessage, this));
	gaia::GuiManager::getInstance()->getWidget<gaia::TextField>("chatBox")->setEnabled(false);

	Message msg = MessageBuilder::clOkSendMeInfos();
	sendMessage(msg);//, game.getFirstLocal());
	//gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	//manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));

	//manager->getWidget<gaia::Button>("soloButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicSolo, this));
}

bool SLobby::catchEvent(const sf::Event& ev)
{
	//Game& game = getGameEngine()->getGame();

	gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));

	return false;
}

void SLobby::update()
{
	processQueue();

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SLobby::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::SV_YOUR_ID:
	{
		int id;
		if (!MessageBuilder::extractSvYourId(msg, id))
			return;

		Game& game = getGameEngine()->getGame();

		game.addLocalId(id);
	}
	break;

	case Message::MessageType::SV_PLAYER_INFOS:
	{
		std::vector<int> ids;
		std::vector<std::string> nicks;
		if (!MessageBuilder::extractSvPlayerInfos(msg, ids, nicks))
			return;

		Game& game = getGameEngine()->getGame();

		for (unsigned int i = 0; i < ids.size(); i++)
		{
			game.createPlayer(ids[i], nicks[i]);
			gaia::GuiManager::getInstance()->getWidget<gaia::ListBox>("listBox")->addItem(
				gaia::PtrTextListBoxItem(new gaia::TextListBoxItem(nicks[i])));
		}
	}
	break;

	case Message::MessageType::SV_NEW_TURN:
	{
		int id;
		if (!MessageBuilder::extractSvNewTurn(msg, id))
			return;

		Game& game = getGameEngine()->getGame();

		game.setTurnTo(id);
	}
	break;

	case Message::MessageType::SV_NEXT_STATE:
	{
		getGameEngine()->setClientGameState(GameState::ptr(new SGameBeginning));
	}
	break;

	case Message::MessageType::SV_SEND_CHAT_MESSAGE:
	{
		std::string chatMsg;
		if (!MessageBuilder::extractSvSendChatMessage(msg, chatMsg))
			return;

		gaia::GuiManager* manager = gaia::GuiManager::getInstance();
		std::string text = manager->getWidget<gaia::TextField>("chatBox")->getText();

		if (text != "")
			text += "\n";
		text += chatMsg;

		manager->getWidget<gaia::TextField>("chatBox")->setText(text);
	}
	break;

	default:
		break;
	}
}

void SLobby::onSendChatMessage(gaia::KeyboardEvent& ev)
{
	if (ev.getKey() == gaia::Keyboard::RETURN)
	{
		gaia::GuiManager* manager = gaia::GuiManager::getInstance();
		std::string strMsg = manager->getWidget<gaia::TextBox>("sendBox")->getText();

		Game& game = getGameEngine()->getGame();

		if (strMsg != "")
		{
			Message msg = MessageBuilder::clSendChatMessage(strMsg);
			sendMessage(msg, game.getFirstLocalId());

			manager->getWidget<gaia::TextBox>("sendBox")->setText("");
		}
	}
}