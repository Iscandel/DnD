#pragma once
#include "Message.h"

#include "Direction.h"
#include "Maze.h"
#include "tools/Point.h"

class Game;

class MessageBuilder
{
public:
	MessageBuilder(void);
	~MessageBuilder(void);

	static Message SvNewPlayer(int id, int team, const std::string& name);
	static Message clDragonAwakes();
	static Message clDragoonMoves(Direction vert, Direction horiz);
	static Message clMove(Direction direction);
	static Message clPlayerLooses(int id);
	static Message clPlayerWounded(int id);
	static Message clEndTurn();
	static Message svWall();
	static Message svPlayerMove(int id, const Point<int>& coords);
	static Message svMaze(const Maze::ptr maze);
	static Message svNewTurn(int id);
	static Message svDragonAwakes();
	static Message svDragoonMoves();
	static Message svTakeTreasure(int id);
	static Message svGameWon(int id);
	static Message svPlayerWounded(int id, int numberOfLives);
	static Message svPlayerLooses(int id);

	static bool extractClMove(const Message& msg, Direction& direction, int& id);
	static bool extractClDragoonMoves(const Message& msg, Direction& vert, Direction& horiz, int& id);
	static bool extractClPlayerLooses(const Message& msg, int& id);
	static bool extractClPlayerWounded(const Message& msg, int& id);
	static bool extractClEndTurn(const Message& msg, int& id);
	static bool extractSvNewTurn(const Message& msg, int& id);
	static bool extractSvTakeTreasure(const Message& msg, int& id);
	static bool extractSvGameWon(const Message& msg, int& id);
	static bool extractSvPlayerWounded(const Message& msg, int& id, int& numberLives);
};