#pragma once
#include "Entity.h"

#include "tools/Rng.h"

#include "Player.h"

class Game;
class GameState;

class Dragoon :
	public GraphicEntity, public WithSmartPtr<Dragoon>
{
//public:
//	typedef std::shared_ptr<Dragoon> ptr;

public:
	using ptr = WithSmartPtr<Dragoon>::ptr;

public:
	Dragoon(int id, Game* game = nullptr);
	~Dragoon();

	void update(GameState& state, const Game& game, unsigned int);

	bool onMoved(SGameServer& state) override;

	int getDistanceTo(const Point<int>& pos);

	double getEuclideanDistanceTo(const Point<int>& pos);

	bool isAwake() const { return myIsAwake; }

	void awake() { myIsAwake = true; }

	bool awakeIfSucceed(const Point<int>& pos);

	Player::ptr chooseTarget();

	void moveToChoosenPlayer(GameState& state, Player::ptr player);

	void returnToTreasureRoom(GameState& state);

	bool isReadyToAttack(const Point<int>& pos);
	
	void attack(SGameServer& state, Player&);

	Player::ptr getWeakestPlayerOnDragoonCell();
	//Dragoon receives player that just moved
	bool onArrivedOnCell(SGameServer&state, Player& player);

	bool onArrivedOnCell(SGameServer&, Dragoon&);

protected:
	bool myIsAwake;
	Game* myGame;
	Rng myRng;
};

