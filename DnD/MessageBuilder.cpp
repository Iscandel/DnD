#include "MessageBuilder.h"

#include <sstream>

MessageBuilder::MessageBuilder(void)
{
}


MessageBuilder::~MessageBuilder(void)
{
}

Message MessageBuilder::clDragonAwakes()
{
	Message msg;

	msg.type = Message::MessageType::CL_DRAGOON_AWAKES;
	//msg.iData[Message::Key::ClCardMovedToHand::CARD_ID] = cardId;

	return msg;
}

Message MessageBuilder::SvNewPlayer(int id, int team, const std::string& name)
{
	Message msg;

	//msg.type = Message::MessageType::SV_NEW_PLAYER;
	//msg.iData[Message::Key::SvNewPlayer::ID] = id;
	//msg.iData[Message::Key::SvNewPlayer::TEAM] = team;
	//msg.sData[Message::Key::SvNewPlayer::NAME] = name;

	return msg;
}

Message MessageBuilder::clMove(Direction direction)
{
	Message msg;

	msg.type = Message::MessageType::CL_MOVE;

	msg.iData[Message::Key::clMove::DIRECTION] = direction;

	return msg;
}

Message MessageBuilder::clDragoonMoves(Direction vert, Direction horiz)
{
	Message msg;

	msg.type = Message::MessageType::CL_DRAGOON_MOVES;

	msg.iData[Message::Key::clDragoonMoves::DIRECTION_HORIZ] = horiz;
	msg.iData[Message::Key::clDragoonMoves::DIRECTION_VERT] = vert;

	return msg;
}

Message MessageBuilder::clPlayerLooses(int id)
{
	Message msg;

	msg.type = Message::MessageType::CL_PLAYER_LOOSES;

	msg.iData[Message::Key::clPlayerLooses::ID] = id;

	return msg;
}

Message MessageBuilder::clPlayerWounded(int id)
{
	Message msg;

	msg.type = Message::MessageType::CL_PLAYER_WOUNDED;

	msg.iData[Message::Key::clPlayerWounded::ID] = id;

	return msg;
}

Message MessageBuilder::clEndTurn()
{
	Message msg;

	msg.type = Message::MessageType::CL_END_TURN;

	return msg;
}
Message MessageBuilder::svPlayerMove(int id, const Point<int>& coords)
{
	Message msg;

	msg.type = Message::MessageType::SV_MOVE;

	msg.iData[Message::Key::SvMove::ID] = id;
	msg.iData[Message::Key::SvMove::X] = coords.x;
	msg.iData[Message::Key::SvMove::Y] = coords.y;

	return msg;
}

Message MessageBuilder::svMaze(const Maze::ptr maze)
{
	Message msg;

	//msg.type = Message::MessageType::SV_MAZE;

	//std::string mazeString;
	//std::ostringstream stream;
	//stream << maze->getSizeX() << " " << maze->getSizeY();

	//for (int i = 0; i < maze->getSizeY(); i++)
	//{
	//	for (int j = 0; j < maze->getSizeX(); j++)
	//	{
	//		Cell::ptr cell = maze->getCell(j, i);
	//		//cell->getSide
	//		
	//	}

	//}

	//msg.iData[Message::Key::SvMove::ID] = id;
	//msg.iData[Message::Key::SvMove::X] = coords.x;
	//msg.iData[Message::Key::SvMove::Y] = coords.y;

	return msg;
}

Message MessageBuilder::svWall()
{
	Message msg;

	msg.type = Message::MessageType::SV_WALL;

	return msg;
}

Message MessageBuilder::svNewTurn(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_NEW_TURN;
	msg.iData[Message::Key::SvNewTurn::ID] = id;

	return msg;
}

Message MessageBuilder::svDragonAwakes()
{
	Message msg;

	msg.type = Message::MessageType::SV_DRAGOON_AWAKES;
	//msg.iData[Message::Key::ClCardMovedToHand::CARD_ID] = cardId;

	return msg;
}

Message MessageBuilder::svDragoonMoves()
{
	Message msg;

	msg.type = Message::MessageType::SV_DRAGOON_MOVES;

	return msg;
}

Message MessageBuilder::svTakeTreasure(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_TAKE_TREASURE;

	msg.iData[Message::Key::SvTakeTreasure::ID] = id;

	return msg;
}

Message MessageBuilder::svGameWon(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_GAME_WON;

	msg.iData[Message::Key::SvGameWon::ID] = id;

	return msg;
}

Message MessageBuilder::svPlayerWounded(int id, int numberOfLives)
{
	Message msg;

	msg.type = Message::MessageType::SV_PLAYER_WOUNDED;

	msg.iData[Message::Key::SvPlayerWounded::ID] = id;
	msg.iData[Message::Key::SvPlayerWounded::NUMBER_LIVES] = numberOfLives;

	return msg;
}

Message MessageBuilder::svPlayerLooses(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_PLAYER_LOOSES;

	msg.iData[Message::Key::SvPlayerLooses::ID] = id;

	return msg;
}

bool MessageBuilder::extractClMove(const Message& msg, Direction& direction, int& id)
{
	if (msg.iData.find(Message::Key::clMove::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::clMove::DIRECTION) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::clMove::ID];
	direction = (Direction)msg.iData[Message::Key::clMove::DIRECTION];

	return true;
}

bool MessageBuilder::extractSvNewTurn(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::SV_NEW_TURN || 
		msg.iData.find(Message::Key::SvNewTurn::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvNewTurn::ID];

	return true;
}

bool MessageBuilder::extractClDragoonMoves(const Message& msg, Direction& vert, Direction& horiz, int& id)
{
	if (msg.type != Message::MessageType::CL_DRAGOON_MOVES ||
		msg.iData.find(Message::Key::clDragoonMoves::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::clDragoonMoves::DIRECTION_HORIZ) == msg.iData.end() ||
		msg.iData.find(Message::Key::clDragoonMoves::DIRECTION_VERT) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::clDragoonMoves::ID];
	horiz = (Direction) msg.iData[Message::Key::clDragoonMoves::DIRECTION_HORIZ];
	vert = (Direction) msg.iData[Message::Key::clDragoonMoves::DIRECTION_VERT];

	return true;
}

bool MessageBuilder::extractClPlayerLooses(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::CL_PLAYER_LOOSES ||
		msg.iData.find(Message::Key::clPlayerLooses::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::clPlayerLooses::ID];

	return true;
}

bool MessageBuilder::extractClEndTurn(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::CL_END_TURN ||
		msg.iData.find(Message::Key::ClEndTurn::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::ClEndTurn::ID];

	return true;
}

bool MessageBuilder::extractClPlayerWounded(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::CL_PLAYER_WOUNDED ||
		msg.iData.find(Message::Key::clPlayerWounded::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::clPlayerWounded::ID];

	return true;
}

bool MessageBuilder::extractSvTakeTreasure(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::SV_TAKE_TREASURE ||
		msg.iData.find(Message::Key::SvTakeTreasure::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvTakeTreasure::ID];

	return true;
}

bool MessageBuilder::extractSvGameWon(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::SV_GAME_WON ||
		msg.iData.find(Message::Key::SvGameWon::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvGameWon::ID];

	return true;
}

bool MessageBuilder::extractSvPlayerWounded(const Message& msg, int& id, int& numberLives)
{
	if (msg.type != Message::MessageType::SV_PLAYER_WOUNDED||
		msg.iData.find(Message::Key::SvPlayerWounded::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvPlayerWounded::NUMBER_LIVES) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvPlayerWounded::ID];
	numberLives = msg.iData[Message::Key::SvPlayerWounded::NUMBER_LIVES];

	return true;
}
