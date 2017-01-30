#pragma once
#include "Message.h"

#include "Direction.h"
#include "Maze.h"
#include "tools/Point.h"

#include <string>

class Game;

class MessageBuilder
{
public:
	MessageBuilder(void);
	~MessageBuilder(void);

	static Message connection(const std::string& ip, const std::string& pseudo);
	static Message SvNewPlayer(int id, int team, const std::string& name);
	static Message clChoosesSecretRoom(int x, int y);
	static Message clDragonAwakes();
	static Message clDragoonMoves(Direction vert, Direction horiz);
	static Message clMove(Direction direction);
	static Message clPlayerLooses(int id); //called by server
	static Message clPlayerWounded(int id); //called by server
	static Message clEndTurn();
	static Message clEndTurn(int id); //called by server
	static Message svWall(int cellX, int cellY, Direction direction);
	static Message svPlayerMove(int id, const Point<int>& coords);
	static Message svMaze(const Maze::ptr maze);
	static Message svNewTurn(int id);
	static Message svDragonAwakes();
	static Message svDragoonMoves();
	static Message svTakeTreasure(int id);
	static Message svGameWon(int id);
	static Message svPlayerTakesTreasureFromPlayer(int winnerId);
	static Message svPlayerWounded(int id, int numberOfLives);
	static Message svPlayerLooses(int id);
	static Message svGameRunning();
	static Message svConnectionResult(int result, int error);

	static bool extractConnection(const Message& msg, std::string& ip, std::string& pseudo);
	static bool extractClChoosesSecretRoom(const Message& msg, int& id, int& x, int& y);
	static bool extractClMove(const Message& msg, Direction& direction, int& id);
	static bool extractClDragoonMoves(const Message& msg, Direction& vert, Direction& horiz, int& id);
	static bool extractClPlayerLooses(const Message& msg, int& id);
	static bool extractClPlayerWounded(const Message& msg, int& id);
	static bool extractClEndTurn(const Message& msg, int& id);
	static bool extractSvNewTurn(const Message& msg, int& id);
	static bool extractSvTakeTreasure(const Message& msg, int& id);
	static bool extractSvGameWon(const Message& msg, int& id);
	static bool extractSvPlayerWounded(const Message& msg, int& id, int& numberLives);
	static bool extractSvWall(const Message& msg, int& cellX, int& cellY, Direction& direction);
	static bool extractSvPlayerTakesTreasureFromPlayer(const Message& msg, int& winnerId);
	static bool extractSvConnectionResult(const Message& msg, int& result, int& error);
};