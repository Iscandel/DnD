#pragma once


#include <iostream>
#include <vector>
#include "tools/WithSmartPtr.h"

#include "Entity.h"
#include "tools/Rng.h"

class Game;

class Player : public GraphicEntity, public WithSmartPtr<Player>
{
public:
	enum Lives {
		LIVE_1 = 1,
		LIVE_2 = 2,
		LIVE_3 = 3
	};
	enum StepsByLives {
		STEPS_1 = 4,
		STEPS_2 = 6,
		STEPS_3 = 8
	};

public:
	using ptr = WithSmartPtr<Player>::ptr;

public:
	typedef std::map<Lives, StepsByLives> MapStepsByLives;

public:
	Player(int id, Game* game = NULL);
	~Player(void);

	void update(GameState& state, const Game& game, unsigned int elapsedTime);

	//void setState(boost::shared_ptr<EntityState<Player> > state);

	void setName(const std::string& name) { myName = name; }

	const std::string& getName() const { return myName; }

	void setGame(Game* game) { myGame = game; }
	const Game& getGame() const { return *myGame; }
	Game& getGame() { return *myGame; }

	void setCurrentStepsRemaining(int nb) { myCurrentStepsRemaining = nb; }
	int getCurrentStepsRemaining() const { return myCurrentStepsRemaining; }
	void doStep() { myCurrentStepsRemaining--; myStrength--; std::cout << "il reste " << myCurrentStepsRemaining << std::endl; }
	bool hasStepsRemaining() const { return myCurrentStepsRemaining > 0; }
	void resetStepsRemaining() { myCurrentStepsRemaining = getMaxSteps(); }
	int getMaxSteps() const;

	int getStrength() const { return myStrength; }
	void tryRenewStrength();

	Lives getNumberOfLives() const { return myLives; }
	bool hasMoreThanOneLife() const { return myLives > LIVE_1; }
	void removeOneLife();
	void setNumberOfLives(Lives lives) { myLives = lives; }

	const Point<int> getSecretRoomPos() const { return mySecretRoom; }

	void setSecretRoomPos(const Point<int>& pos) { mySecretRoom = pos; }

	void setTreasure(bool treasure);
	bool hasTreasure() const { return myHasTreasure; }

	bool onMoved(SGameServer& state) override;

	//Player receives player moving
	bool onArrivedOnCell(SGameServer& state, Player& player);

	//Player receives dragoon
	bool onArrivedOnCell(SGameServer& state, Dragoon& dragoon);

	bool isInSecretRoom() const { return myAbstractPos == getSecretRoomPos(); }
	
	void fightForTreasure(SGameServer& state, Player& player);

	// bool Player::onArrivedOnCell(GameState::ptr state, Treasure::ptr treasure)
	// {
	//	return false;
	// }

	//void isHuman() {return myIsHuman;}

	//void setGame(const Game& game) {myGame = game;}
	//const Game& getGame() {return myGame;}

protected:
	//PtrTeam myTeam;
	//std::vector<PtrCard> myCards;
	std::string myName;
	//std::shared_ptr<EntityState<Player> > myState;

	Game* myGame;

	Point<int> mySecretRoom;
	//int myX;
	//int myY;

	int myCurrentStepsRemaining;
	Lives myLives;
	StepsByLives myCurrentMaxSteps;

	MapStepsByLives myStepsByLives;

	bool myHasTreasure;

	int myStrength;

	const int RENEW_STRENGTH_FREQ;
	const int MAX_STRENGTH;
	const int STEPS_TREASURE;

	Rng myRandom;
};

//typedef boost::shared_ptr<Player> PtrPlayer;
