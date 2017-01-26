#pragma once
#include "Entity.h"

class Game;

class Treasure :
	public GraphicEntity
{
public:
	using ptr = WithSmartPtr<Treasure>::ptr;

public:
	Treasure(int id, Game* game = NULL);
	~Treasure();

	virtual void update(GameState& state, const Game& game, unsigned int elapsed) override {}

	bool onArrivedOnCell(SGameServer&, Player& player) override;

	bool onArrivedOnCell(SGameServer&, Dragoon&) override;

	bool setTaken(bool taken) { myIsTaken = taken; }
	bool wasTaken() const { return myIsTaken; }

	void takeTreasure(SGameServer& state, Player& player);

protected:
	bool myIsTaken;
	Game* myGame;
};

