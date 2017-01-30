#include "SMainMenuSolo.h"

#include "GameEngine.h"
#include "Game.h"
#include "GraphicEngine.h"
#include "MainMenuView.h"
#include "SGameBeginning.h"
#include "SGameBeginningServer.h"

SMainMenuSolo::SMainMenuSolo()
{
}


SMainMenuSolo::~SMainMenuSolo()
{
}

void SMainMenuSolo::init()
{
	setView(View::ptr(new MainMenuView));
	gaia::GuiManager::getInstance()->clean();
	gaia::xml::XMLGuiLoader::loadGUI("data/gui/guiMainMenuSolo.xml");

	gaia::GuiManager* manager = gaia::GuiManager::getInstance();

	manager->getWidget<gaia::Button>("onePlayer")->subscribeMouseReleased(gaia::my_bind(&SMainMenuSolo::onClic1P, this));
	manager->getWidget<gaia::Button>("twoPlayers")->subscribeMouseReleased(gaia::my_bind(&SMainMenuSolo::onClic2P, this));

}

bool SMainMenuSolo::catchEvent(const sf::Event& ev)
{
	gaia::GuiManager::getInstance()->processEvent(gaia::SFMLInput(ev));
	//if (ev.type == sf::Event::KeyPressed)
	//{
	//	//setClientGameState(GameState::ptr(new SMainMenu));
	//}

	return true;
}

void SMainMenuSolo::update()
{
	processQueue();

	gaia::GuiManager::getInstance()->update(getGraphicEngine()->getElapsedTime());
}

void SMainMenuSolo::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	default:
		break;
	}
}

void SMainMenuSolo::onClic1P(gaia::MouseEvent& ev)
{
	Game& game = getGameEngine()->getGame();
	game.reset();
	game.setup1PGame("Player 1");
	setServerGameState(GameState::ptr(new SGameBeginningServer));
	setClientGameState(GameState::ptr(new SGameBeginning));
}

void SMainMenuSolo::onClic2P(gaia::MouseEvent& ev)
{
	Game& game = getGameEngine()->getGame();
	game.reset();
	game.setup2PGame("Player 1", "Player 2");
	setServerGameState(GameState::ptr(new SGameBeginningServer));
	setClientGameState(GameState::ptr(new SGameBeginning));
}