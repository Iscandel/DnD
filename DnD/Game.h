#pragma once

#include "BaseMazeGenerator.h"
#include "Dragoon.h"
#include "EntityManager.h"
#include "Maze.h"
#include "Player.h"
#include "Treasure.h"

class PlayerDef;
class CellDef;
class GameState;

class Game
{
public:
	Game();
	~Game();

	Maze::ptr getMaze() { return myMaze; }

	EntityManager& getManager() { return myManager; }

	//int getIdToPlay() const { return myIdToPlay; }

	int getMazeUnperfectPerc() const { return myMazeUnperfectPerc; }
	int getMazeSize() const { return myMazeSize; }

	Maze::ptr createMaze(BaseMazeGenerator& generator, int x, int y);

	void update(GameState& state, unsigned int elapsedTime);

	int nextEntityTurn();
	int nextPlayerTurn();

	Dragoon::ptr getDragoon();
	Treasure::ptr getTreasure();
	std::vector<Entity::ptr> getEntities();
	Entity::ptr getEntity(int id);
	Player::ptr getPlayer(int id);
	std::vector<Player::ptr> getPlayers();

	bool isNickPresent(const std::string& nick);

	int getCurrentIdTurn() const { return myCurrentIdTurn; }
	void setTurnTo(int id) { myCurrentIdTurn = id; }
	void setTurnToFirstPlayer();

	int getFirstLocalId() const {
		if (myLocalIds.size() > 0) 
			{ return myLocalIds[0]; } 
		return 0;
	}
	std::vector<int> getLocalIds() { return myLocalIds; }
	bool isLocalId(int id) const;

	bool addLocalId(int id);

	void setWinner(Player::ptr winner) { myWinner = winner; }
	Player::ptr getWinner() { return myWinner; }

	Player::ptr createPlayer(const std::string& nick, bool isLocal, bool isAI = false);
	//Client function
	Player::ptr Game::createPlayer(int id, const std::string& nick);

	void reset();

	void setup1PGame(const std::string& name);

	void setup2PGame(const std::string& p1, const std::string& p2);

protected:
	void initDefaultMaze();

	PlayerDef& getIndexPlayerDef(int index);
	CellDef& getIndexCellDef(int index);

protected:
	Maze::ptr myMaze;
	EntityManager myManager;

	//int myIdToPlay;

	int myMazeUnperfectPerc;
	int myMazeSize;

	int myCurrentIdTurn;

	std::vector<int> myLocalIds;

	Player::ptr myWinner;

	const std::string DRAGOON_NAME;
};

