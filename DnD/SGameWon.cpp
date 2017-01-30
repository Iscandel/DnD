#include "SGameWon.h"

#include "GameWonView.h"
#include "SMainMenu.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

SGameWon::SGameWon()
{
}


SGameWon::~SGameWon()
{
}

void SGameWon::init()
{
	setView(View::ptr(new GameWonView("data/gameWonViewPos.txt")));

	gaia::GuiManager::getInstance()->clean();
}

bool SGameWon::catchEvent(const sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		setClientGameState(GameState::ptr(new SMainMenu));
	}

	return true;
}

void SGameWon::update()
{
	processQueue();
}

void SGameWon::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	default:
		break;
	}
}