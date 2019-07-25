#include "SGameWon.h"

#include "graphic/GameWonView.h"
#include "graphic/GameLostView.h"
#include "SMainMenu.h"

#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer.h"
#include "Gaia/XMLGaia.h"

SGameWon::SGameWon(bool won)
:myIsWon(won)
{
}


SGameWon::~SGameWon()
{
}

void SGameWon::init()
{
	if(myIsWon)
		setView(View::ptr(new GameWonView("data/gameWonViewPos.txt")));
	else
		setView(View::ptr(new GameLostView));

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