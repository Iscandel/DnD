#include "GameView.h"
#include "GameState.h"
//#include "Game.h"
#include "TextureManager.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "tools/FileReading.h"


GameView::GameView(const std::string& path)
{
	loadViewPosition(path);
}


GameView::~GameView(void)
{
}

void GameView::loadViewPosition(const std::string& path)
{
	TextFile file(path);
	int nbElements = 0;

	file >> nbElements;
	for (int i = 0; i < nbElements; i++)
	{
		std::string string;
		double posX, posY;
		file >> string >> posX >> posY;
		myPositions.insert(std::make_pair(string, Point<double>(posX, posY)));
	}
}

void GameView::draw(GameState& state)
{
	//Game& game = state.getGameEngine()->getGame();
	//int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
	//int windowSizeY = state.getGraphicEngine()->getWindowSizeY();

	//PtrResourceTexture fond = TextureManager::getInstance()->getResource(2);

	//sf::Sprite spFond;
	//spFond.SetTexture(*fond->getTexture());
	//spFond.SetPosition(0, 0);
	//spFond.SetScale((float)windowSizeX / fond->getTexture()->GetWidth(), (float)windowSizeY / fond->getTexture()->GetHeight());
	//state.getGraphicEngine()->draw(spFond);

	////Players
	//int number = game.getNumberPlayers();
	//for (int i = 0; i < number; i++)
	//{
	//	PtrPlayer player = game.getPlayerByPosition(i);
	//	const std::vector<PtrCard>& cards = player->getCards();

	//	//std::cout << (static_cast<CardHandler<Player>* >(player)) << std::endl;
	//	drawCards(state, cards);
	//	PtrTeam team = game.getTeam(player->getId());
	//	sf::String string(tools::numToString(team->getTeamId()) + ". " + player->getName());
	//	sf::Text text(string);
	//	text.SetCharacterSize(15);
	//	Point<double> pos = getGivenPosition("4p_p" + tools::numToString(i + 1) + "Name");
	//	text.SetPosition(pos.x * windowSizeX, pos.y * windowSizeY);
	//	state.getGraphicEngine()->draw(text);
	//}

	////Table (no ref)
	//std::vector<PtrCard> cards = game.getTable().getCards();
	//drawCards(state, cards);

	////TrickSet (no ref)
	//cards = game.getTrickSet().getCards();
	//drawCards(state, cards);
}

//void GameView::drawCards(GameState& state, const std::vector<PtrCard>& cards)
//{
//	int windowSizeX = state.getGraphicEngine()->getWindowSizeX();
//	int windowSizeY = state.getGraphicEngine()->getWindowSizeY();
//	for (unsigned int j = 0; j < cards.size(); j++)
//	{
//		sf::Sprite sp;
//		//PtrResourceImage resource;
//		//if(i == 0)
//		//	resource = cards[j]->getCurrentImage(); //Il faudrait un vecteur de rect et la texture associée (cas multi images). Ou alors renvoyer un vec + 2ème fonction std::vec<int> getCurrentNumImages() 
//		//else
//		//	resource = cards[j]->getImageBack();
//		std::vector<Image>& resource = cards[j]->getCurrentImages();
//		//if(resource)
//		for (unsigned int k = 0; k < resource.size(); k++)
//		{
//			PtrTexture texture = resource[k].getResourceTexture()->getTexture();
//			//PtrTexture texture = resource->getResourceTexture()->getTexture(); 
//			//Optimization
//			//if(k == 0 || (k > 0 && resource[k].getTextureId() != resource[k - 1].getTextureId()))
//			{
//				sp.SetTexture(*texture);
//			}
//
//			IntRect rect = resource[k].getRect();
//			//IntRect rect = resource->getImage().getRect();
//			sf::IntRect sfRect(rect.x, rect.y, rect.width, rect.height);
//			sp.SetTextureRect(sfRect);
//			sp.SetScale((cards[j]->getRelSizeX() * (double)windowSizeX) / rect.width,
//				(cards[j]->getRelSizeY() * (double)windowSizeY) / rect.height);
//			//rotation is in clockwise order for SFML
//			sp.SetRotation(-cards[j]->getRotation());
//
//			sp.SetPosition(cards[j]->getX() * windowSizeX, cards[j]->getY() * windowSizeY);
//
//			if (cards[j]->isSelected())
//			{
//				sp.SetColor(sf::Color(100, 100, 200));
//			}
//
//			state.getGraphicEngine()->draw(sp);
//		}
//	}
//}