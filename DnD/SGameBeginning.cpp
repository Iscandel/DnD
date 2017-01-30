#include "SGameBeginning.h"

#include "GameEngine.h"
#include "GameBeginningView.h"
#include "GraphicEngine.h"
#include "MessageBuilder.h"
#include "NetworkEngine.h"
#include "SGame.h"

#include "Gaia/addFactory.h"
#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"
#include "DraggableImage.h"

SGameBeginning::SGameBeginning()
{
}


SGameBeginning::~SGameBeginning()
{
}

void SGameBeginning::init()
{
	gaia::addFactory<DraggableImage>();

	setView(View::ptr(new GameBeginningView("data/gameViewPos.txt")));

	gaia::GuiManager::getInstance()->clean();
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiGame.xml");

	gaia::GuiManager* manager = gaia::GuiManager::getInstance();
	manager->getWidget<gaia::TextBox>("sendBox")->setTextColor(gaia::Color(255, 255, 255));


	//manager->getWidget<gaia::Button>("soloButton")->subscribeMouseReleased(gaia::my_bind(&SMainMenu::onClicSolo, this));
}

bool SGameBeginning::catchEvent(const sf::Event& ev)
{
	Game& game = getGameEngine()->getGame();

	if (!gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev)))
	{
		if (ev.type == sf::Event::KeyPressed)
		{
			
			if (ev.key.code == sf::Keyboard::Right)
			{
				if (game.isLocalId(game.getCurrentIdTurn()))
				{
					Player::ptr player = game.getPlayer(game.getCurrentIdTurn());
					const Point<int>& roomPos = player->getSecretRoomPos();
					//Client sets itself the secret room pos, but it doesn't matter.
					//Server validates
					if (roomPos.x < game.getMaze()->getSizeX() - 1)
					{
						player->setSecretRoomPos(Point<int>(roomPos.x + 1, roomPos.y));
						player->setAbstractPosition(player->getSecretRoomPos());
					}
				}
			}

			else if (ev.key.code == sf::Keyboard::Left)
			{
				if (game.isLocalId(game.getCurrentIdTurn()))
				{
					Player::ptr player = game.getPlayer(game.getCurrentIdTurn());
					const Point<int>& roomPos = player->getSecretRoomPos();
					//Client sets itself the secret room pos, but it doesn't matter.
					//Server validates
					if (roomPos.x > 0)
					{
						player->setSecretRoomPos(Point<int>(roomPos.x - 1, roomPos.y));
						player->setAbstractPosition(player->getSecretRoomPos());
					}
				}
			}

			else if (ev.key.code == sf::Keyboard::Up)
			{
				if (game.isLocalId(game.getCurrentIdTurn()))
				{
					Player::ptr player = game.getPlayer(game.getCurrentIdTurn());
					const Point<int>& roomPos = player->getSecretRoomPos();
					//Client sets itself the secret room pos, but it doesn't matter.
					//Server validates
					if (roomPos.y > 0)
					{
						player->setSecretRoomPos(Point<int>(roomPos.x, roomPos.y - 1));
						player->setAbstractPosition(player->getSecretRoomPos());
					}
				}
			}

			else if (ev.key.code == sf::Keyboard::Down)
			{
				if (game.isLocalId(game.getCurrentIdTurn()))
				{
					Player::ptr player = game.getPlayer(game.getCurrentIdTurn());
					const Point<int>& roomPos = player->getSecretRoomPos();
					//Client sets itself the secret room pos, but it doesn't matter.
					//Server validates
					if (roomPos.y < game.getMaze()->getSizeY() - 1)
					{
						player->setSecretRoomPos(Point<int>(roomPos.x, roomPos.y + 1));
						player->setAbstractPosition(player->getSecretRoomPos());
					}
				}
			}

			else if (ev.key.code == sf::Keyboard::Space)
			{
				if (game.isLocalId(game.getCurrentIdTurn()))
				{
					Player::ptr player = game.getPlayer(game.getCurrentIdTurn());
					const Point<int>& roomPos = player->getSecretRoomPos();
					Message msg = MessageBuilder::clChoosesSecretRoom(roomPos.x, roomPos.y);
					sendMessage(msg, getGameEngine()->getGame().getCurrentIdTurn());
				}
			}
		}
	}

	return false;
}

void SGameBeginning::update()
{
	processQueue();

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SGameBeginning::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	case Message::MessageType::SV_GAME_RUNNING:
	{
		setClientGameState(GameState::ptr(new SGame));
	}
	break;

	default:
		break;
	}
}