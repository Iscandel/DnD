#include "SGame.h"

#include "GameEngine.h"
#include "GameView.h"
#include "GraphicEngine.h"
#include "MessageBuilder.h"
#include "NetworkEngine.h"
#include "TextureManager.h"
#include "tools/Logger.h"
//#include "tools/Tools.h"

#include "CompleteMazeGenerator.h"

SGame::SGame(void)
{
}


SGame::~SGame(void)
{
}

void SGame::init()
{
	setView(View::ptr(new GameView("data/gameViewPos.txt")));

	Maze::ptr maze = getGameEngine()->getGame().getMaze();
	for (int i = 0; i < maze->getSizeY(); i++)
	{
		for (int j = 0; j < maze->getSizeX(); j++)
		{
			Cell::ptr cell = maze->getCell(j, i);
			Point<double>& pos = myView->getGivenPosition("cellSize");
			cell->setRelSize(pos.x, pos.y);
		}
	}
}

bool SGame::catchEvent(const sf::Event& ev)
{
	//Game& game = getGameEngine()->getGame();
	//EntityManager entityManager = game.getEntityManager();

	//if (ev.Type == sf::Event::MouseMoved)
	//{
	//	if (entities.size() != 0)
	//	{
	//		entities.back()->setSelected(true);
	//		//Message msg = MessageBuilder::clCardToPlay(entities.back()->getId());
	//		//clientRequestTCP(msg);
	//	}
	//}
	////if(ev.Type == sf::Event::MouseMoved)
	////{
	////	std::vector<PtrGraphicEntity> allEntities = entityManager.getEntities();
	////	for(unsigned int i = 0; i < allEntities.size(); i++)
	////	{
	////		allEntities[i]->setSelected(false);
	////	}

	////	std::vector<PtrGraphicEntity> entities = 
	////		entityManager.getHoveredEntities(
	////			Point<double>(ev.MouseMove.X / getGraphicEngine()->getWindowSizeX(), 
	////						  ev.MouseMove.Y / getGraphicEngine()->getWindowSizeY())); //A modif
	////	if(entities.size() != 0)
	////	{
	////		entities.back()->setSelected(true);
	////		Message msg = MessageBuilder::clCardToPlay(entities.back()->getId());
	////		clientRequestTCP(msg);
	////	}
	////		
	////}

	//if (ev.Type == sf::Event::MouseButtonReleased)
	//{
	//	if (ev.MouseButton.Button == sf::Mouse::Left)
	//	{
	//	}
	//}
	return true;
}

void SGame::update()
{
	processQueue();

	//Game& game = getGameEngine()->getGame();
	//game.update(getGraphicEngine()->getElapsedTime());

	//std::vector<TimerFunction>::iterator it = myTimerFunctions.begin();
	//for (; it != myTimerFunctions.end();)
	//{

	//	it->update(getGraphicEngine()->getElapsedTime());
	//	if (it->isFinished())
	//		it = myTimerFunctions.erase(it);
	//	else
	//		++it;
	//}

	//for(int i = 0; i < game.getNumberPlayers(); i++)
	//{
	//	PtrPlayer player = game.getPlayerByPosition(i);
	//	player->update(game, getGraphicEngine()->getElapsedTime());
	//}

	//game.getTable().update(getGraphicEngine()->getElapsedTime());
}

void SGame::processMessage(const Message& msg)
{
	switch (msg.type)
	{
	default:
		break;
	}
}


//void SGame::draw()
//{
//	Game& game = getGameEngine()->getGame();
//
//	PtrResourceTexture fond = TextureManager::getInstance()->getResource(2);
//
//	float x = 0, y = 0;
//	sf::Sprite spFond;
//	spFond.SetTexture(*fond->getTexture());
//	spFond.SetPosition(0, 0);
//	spFond.SetScale(1.f, 1.f);
//	getGameEngine()->getGraphicEngine()->draw(spFond);
//	
//	int number = game.getNumberPlayers();
//	for(int i = 0; i < number; i++)
//	{
//		x = 0;
//
//		Player* player = game.getPlayer(i);
//		const std::vector<PtrCard>& cards = player->getCards();
//
//		//std::cout << (static_cast<CardHandler<Player>* >(player)) << std::endl;
//
//		for(unsigned int j = 0; j < cards.size(); j++)
//		{
//			PtrResourceImage resource = cards[j]->getImage();
//			PtrTexture texture = resource->getResourceTexture()->getTexture();
//			sf::Sprite sp;
//			sp.SetTexture(*texture);
//			IntRect rect = resource->getImage().getRect();
//			sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//			sp.SetTextureRect(sfRect);
//			sp.SetPosition(x, y);
//
//			cards[j]->setPosition(Point<float>(x, y));
//			cards[j]->setSize(rect.width, rect.height);
//			if(cards[j]->isSelected())
//			{
//				sp.SetColor(sf::Color(100, 100, 200));
//			}
//
//			x += 50;
//
//			getGameEngine()->getGraphicEngine()->draw(sp);
//		}
//
//		y += 300;
//	}
//}
