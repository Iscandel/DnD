#pragma once


#include <vector>
#include "tools/WithSmartPtr.h"

#include "Entity.h"

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
	void doStep() { myCurrentStepsRemaining--; }
	bool hasStepsRemaining() const { return myCurrentStepsRemaining > 0; }
	void resetStepsRemaining() { myCurrentStepsRemaining = myCurrentMaxSteps; }
	int getMaxSteps() const;

	Lives getNumberOfLives() const { return myLives; }
	bool hasMoreThanOneLife() const { return myLives > LIVE_1; }
	void removeOneLife();
	void setNumberOfLives(Lives lives) { myLives = lives; }

	const Point<int> getSecretRoomPos() const { return mySecretRoom; }

	void setSecretRoomPos(const Point<int>& pos) { mySecretRoom = pos; }

	void setTreasure(bool treasure) { myHasTreasure = treasure; }
	bool hasTreasure() const { return myHasTreasure; }

	bool onMoved(SGameServer& state) override;

	//Player receives player moving
	bool onArrivedOnCell(SGameServer& state, Player& player);

	//Player receives dragoon
	bool onArrivedOnCell(SGameServer& state, Dragoon& dragoon);

	bool isInSecretRoom() const { return myAbstractPos == getSecretRoomPos(); }

	void defeat() { myHasLost = true; }
	bool hasLost() const { return myHasLost; }

	// bool Player::onArrivedOnCell(GameState::ptr state, Treasure::ptr treasure)
	// {
	//	return false;
	// }
	//void setTeam(PtrTeam team) {myTeam = team;}

	//PtrTeam getTeam() {return myTeam;}

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

	bool myHasLost;

	const int STEPS_TREASURE;
};

//typedef boost::shared_ptr<Player> PtrPlayer;
