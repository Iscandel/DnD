#include "SLobbyServer.h"

#include "game/GameEngine.h"
#include "game/MessageBuilder.h"
#include "network/NetworkEngine.h"
#include "SGameBeginningServer.h"
#include "gameState/clientState/SLobby.h"

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

	Game& game = getGameEngine()->getGame();
	std::vector<Player::ptr> players = game.getPlayers();

	auto manager = gaia::GuiManager::getInstance();
	manager->getWidget<gaia::Button>("startButton")->setVisible(true);
	manager->getWidget<gaia::ListBox>("listBox")->addItem(
		gaia::PtrTextListBoxItem(new gaia::TextListBoxItem(players[0]->getName())));
	//gaia::GuiManager::getInstance()->clean();
	//gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiMainConnection.xml");

	//gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	//manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));

	manager->getWidget<gaia::Button>("startButton")->subscribeMouseReleased(gaia::my_bind(&SLobbyServer::onClicStart, this));
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
	case Message::MessageType::CL_CONNECTION:
	{
		int tmpId;
		std::string nick;
		if (!MessageBuilder::extractClConnection(msg, tmpId, nick))
			return;

		Game& game = getGameEngine()->getGame();

		if (game.isNickPresent(nick))
		{
			Message m = MessageBuilder::svConnectionResult(0, 0, "Nick already used");
			sendMessageTo(m, tmpId);

			getNetworkEngine()->disconnectPlayer(tmpId, true);
		}
		else
		{
			//create player
			Player::ptr player = game.createPlayer(nick, false);
			//change tmp id
			getNetworkEngine()->changeTemporaryToFinal(tmpId, player->getId());
			//inform player
			Message m = MessageBuilder::svConnectionResult(1, 0, "Nothing");
			sendMessageTo(m, player->getId());

			gaia::GuiManager::getInstance()->getWidget<gaia::ListBox>("listBox")->addItem(
				gaia::PtrTextListBoxItem(new gaia::TextListBoxItem(player->getName())));

			//inform other distant players about the new player
			//m = MessageBuilder::svNewPlayer(id, nick);
			//this->sendMessageToAllExcept(m, id);
		}
	}
	break;

	case Message::MessageType::CL_OK_SEND_ME_INFOS:
	{
		int id;
		if (!MessageBuilder::extractClSendMeInfos(msg, id))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);
		//local can ask, and they do with an invalid player id
		if (player)
		{
			Message msg = MessageBuilder::svPlayerInfos(game);
			sendMessageTo(msg, player->getId());

			msg = MessageBuilder::svYourId(id);
			sendMessageTo(msg, player->getId());
		}
	}

	case Message::MessageType::CL_SEND_CHAT_MESSAGE:
	{
		int id;
		std::string strMessage;
		if (!MessageBuilder::extractClSendChatMessage(msg, id, strMessage))
			return;

		Game& game = getGameEngine()->getGame();
		Player::ptr player = game.getPlayer(id);

		if (player)
		{
			std::string toSend = "[" + player->getName() + "] says: " + strMessage;
	
			Message m = MessageBuilder::svSendChatMessage(toSend);
			sendMessage(m);
		}
	}
	break;

	default:
		break;
	}
}

void SLobbyServer::onClicStart(gaia::MouseEvent& ev)
{
	gaia::GuiManager* manager = gaia::GuiManager::getInstance();

	Game& game = getGameEngine()->getGame();

	Message msg = MessageBuilder::svNewTurn(game.getCurrentIdTurn());
	
	setServerGameState(GameState::ptr(new SGameBeginningServer));
}