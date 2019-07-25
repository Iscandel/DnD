#include "MessageBuilder.h"

#include "Game.h"

#include <sstream>

MessageBuilder::MessageBuilder(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MessageBuilder::~MessageBuilder(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::connection(const std::string& ip, const std::string& pseudo)
{
	Message msg;

	msg.type = Message::MessageType::CONNECTION;

	msg.sData[Message::Key::Connection::IP] = ip;
	msg.sData[Message::Key::Connection::PSEUDO] = pseudo;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clConnection(const std::string& nick)
{
	Message msg;

	msg.type = Message::MessageType::CL_CONNECTION;

	msg.sData[Message::Key::ClConnection::NAME] = nick;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clOkSendMeInfos()
{
	Message msg;

	msg.type = Message::MessageType::CL_OK_SEND_ME_INFOS;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clDragonAwakes()
{
	Message msg;

	msg.type = Message::MessageType::CL_DRAGOON_AWAKES;
	//msg.iData[Message::Key::ClCardMovedToHand::CARD_ID] = cardId;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::SvNewPlayer(int id, int team, const std::string& name)
{
	Message msg;

	//msg.type = Message::MessageType::SV_NEW_PLAYER;
	//msg.iData[Message::Key::SvNewPlayer::ID] = id;
	//msg.iData[Message::Key::SvNewPlayer::TEAM] = team;
	//msg.sData[Message::Key::SvNewPlayer::NAME] = name;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clChoosesSecretRoom(int x, int y)
{
	Message msg;

	msg.type = Message::MessageType::CL_CHOOSES_SECRET_ROOM;

	msg.iData[Message::Key::ClChoosesSecretRoom::X] = x;
	msg.iData[Message::Key::ClChoosesSecretRoom::Y] = y;


	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clMove(Direction direction)
{
	Message msg;

	msg.type = Message::MessageType::CL_MOVE;

	msg.iData[Message::Key::clMove::DIRECTION] = direction;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clDragoonMoves(Direction vert, Direction horiz)
{
	Message msg;

	msg.type = Message::MessageType::CL_DRAGOON_MOVES;

	msg.iData[Message::Key::clDragoonMoves::DIRECTION_HORIZ] = horiz;
	msg.iData[Message::Key::clDragoonMoves::DIRECTION_VERT] = vert;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clPlayerLooses(int id)
{
	Message msg;

	msg.type = Message::MessageType::CL_PLAYER_LOOSES;

	msg.iData[Message::Key::clPlayerLooses::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clPlayerWounded(int id)
{
	Message msg;

	msg.type = Message::MessageType::CL_PLAYER_WOUNDED;

	msg.iData[Message::Key::clPlayerWounded::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clEndTurn()
{
	Message msg;

	msg.type = Message::MessageType::CL_END_TURN;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clEndTurn(int id)
{
	Message msg;

	msg.type = Message::MessageType::CL_END_TURN;

	msg.iData[Message::Key::ClEndTurn::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::clSendChatMessage(const std::string& message)
{
	Message msg;

	msg.type = Message::MessageType::CL_SEND_CHAT_MESSAGE;

	msg.sData[Message::Key::ClSendChatMessage::MESSAGE] = message;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svPlayerMove(int id, const Point<int>& coords)
{
	Message msg;

	msg.type = Message::MessageType::SV_MOVE;

	msg.iData[Message::Key::SvMove::ID] = id;
	msg.iData[Message::Key::SvMove::X] = coords.x;
	msg.iData[Message::Key::SvMove::Y] = coords.y;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svWall(int cellX, int cellY, Direction direction)
{
	Message msg;

	msg.type = Message::MessageType::SV_WALL;

	msg.iData[Message::Key::SvWall::X] = cellX;
	msg.iData[Message::Key::SvWall::Y] = cellY;
	msg.iData[Message::Key::SvWall::DIRECTION] = (int) direction;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svNewTurn(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_NEW_TURN;
	msg.iData[Message::Key::SvNewTurn::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svDragonAwakes()
{
	Message msg;

	msg.type = Message::MessageType::SV_DRAGOON_AWAKES;
	//msg.iData[Message::Key::ClCardMovedToHand::CARD_ID] = cardId;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svDragoonMoves()
{
	Message msg;

	msg.type = Message::MessageType::SV_DRAGOON_MOVES;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svTakeTreasure(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_TAKE_TREASURE;

	msg.iData[Message::Key::SvTakeTreasure::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svPlayerTakesTreasureFromPlayer(int winnerId)
{
	Message msg;

	msg.type = Message::MessageType::SV_PLAYER_TAKES_TREASURE_FROM_PLAYER;

	msg.iData[Message::Key::SvPlayerTakesTreasureFromPlayer::ID_WINNER] = winnerId;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svGameWon(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_GAME_WON;

	msg.iData[Message::Key::SvGameWon::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svPlayerWounded(int id, int numberOfLives)
{
	Message msg;

	msg.type = Message::MessageType::SV_PLAYER_WOUNDED;

	msg.iData[Message::Key::SvPlayerWounded::ID] = id;
	msg.iData[Message::Key::SvPlayerWounded::NUMBER_LIVES] = numberOfLives;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svPlayerLooses(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_PLAYER_LOOSES;

	msg.iData[Message::Key::SvPlayerLooses::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svGameRunning()
{
	Message msg;

	msg.type = Message::MessageType::SV_GAME_RUNNING;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svConnectionResult(int result, int error, const std::string& reason)
{
	Message msg;

	msg.type = Message::MessageType::SV_CONNECTION_RESULT;

	msg.iData[Message::Key::SvConnectionResult::RESULT] = result;
	msg.iData[Message::Key::SvConnectionResult::ERROR_CONNEC] = error;
	msg.sData[Message::Key::SvConnectionResult::REASON] = reason;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svGameOver()
{
	Message msg;

	msg.type = Message::MessageType::SV_GAME_OVER;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svPlayerInfos(Game& game)
{
	Message msg;

	std::vector<Player::ptr> players = game.getPlayers();

	msg.type = Message::MessageType::SV_PLAYER_INFOS;

	msg.iData[Message::Key::SvPlayerInfos::NB_PLAYERS] = players.size();

	std::string str;
	
	for (unsigned int i = 0; i < players.size(); i++)
	{
		str += tools::numToString(players[i]->getId()) + " " + 
			tools::numToString(players[i]->getName().size()) + " " + 
			tools::numToString(players[i]->getName());
		if (i != players.size() - 1)
			str += " ";
	}

	msg.sData[Message::Key::SvPlayerInfos::INFOS] = str;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svYourId(int id)
{
	Message msg;

	msg.type = Message::MessageType::SV_YOUR_ID;

	msg.iData[Message::Key::SvYourID::ID] = id;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svNextState()
{
	Message msg;

	msg.type = Message::MessageType::SV_NEXT_STATE;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svSecretRoomChosen(int id, int x, int y)
{
	Message msg;

	msg.type = Message::MessageType::SV_SECRET_ROOM_CHOSEN;

	msg.iData[Message::Key::SvSecretRoomChosen::ID] = id;
	msg.iData[Message::Key::SvSecretRoomChosen::X] = x;
	msg.iData[Message::Key::SvSecretRoomChosen::Y] = y;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Message MessageBuilder::svSendChatMessage(const std::string& message)
{
	Message msg;

	msg.type = Message::MessageType::SV_SEND_CHAT_MESSAGE;

	msg.sData[Message::Key::SvSendChatMessage::MESSAGE] = message;

	return msg;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractConnection(const Message& msg, std::string& ip, std::string& pseudo)
{
	if (msg.type != Message::MessageType::CONNECTION ||
		msg.sData.find(Message::Key::Connection::IP) == msg.sData.end() ||
		msg.sData.find(Message::Key::Connection::PSEUDO) == msg.sData.end())
	{
		return false;
	}

	ip = msg.sData[Message::Key::Connection::IP];
	pseudo = msg.sData[Message::Key::Connection::PSEUDO];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractClConnection(const Message& msg, int& id, std::string& nick)
{
	if (msg.type != Message::MessageType::CL_CONNECTION ||
		msg.iData.find(Message::Key::ClConnection::TMP_ID) == msg.iData.end() ||
		msg.sData.find(Message::Key::ClConnection::NAME) == msg.sData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::ClConnection::TMP_ID];
	nick = msg.sData[Message::Key::ClConnection::NAME];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractClSendMeInfos(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::CL_OK_SEND_ME_INFOS ||
		msg.iData.find(Message::Key::clOkSendMeInfos::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::clOkSendMeInfos::ID];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractClSendChatMessage(const Message& msg, int& id, std::string& message)
{
	if (msg.type != Message::MessageType::CL_SEND_CHAT_MESSAGE ||
		msg.iData.find(Message::Key::ClSendChatMessage::ID) == msg.iData.end() ||
		msg.sData.find(Message::Key::ClSendChatMessage::MESSAGE) == msg.sData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::ClSendChatMessage::ID];
	message = msg.sData[Message::Key::ClSendChatMessage::MESSAGE];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvPlayerInfos(const Message& msg, std::vector<int>& ids, std::vector<std::string>& nicks)
{
	if (msg.type != Message::MessageType::SV_PLAYER_INFOS ||
		msg.iData.find(Message::Key::SvPlayerInfos::NB_PLAYERS) == msg.iData.end() ||
		msg.sData.find(Message::Key::SvPlayerInfos::INFOS) == msg.sData.end())
	{
		return false;
	}

	int nbPlayers = msg.iData[Message::Key::SvPlayerInfos::NB_PLAYERS];
	std::string str = msg.sData[Message::Key::SvPlayerInfos::INFOS];

	for (int i = 0; i < nbPlayers; i++)
	{
		//L'id
		int pos = str.find(' ');
		int id = tools::stringToNum<int>(str.substr(0, pos));
		ids.push_back(id);
		str = str.substr(pos + 1, str.size() - 1);

		//Nick length
		pos = str.find(' ');
		int nickLength = tools::stringToNum<int>(str.substr(0, pos));
		str = str.substr(pos + 1, str.size() - 1);

		//Le pseudo
		std::string nick = str.substr(0, nickLength);
		nicks.push_back(nick);
		if(i != nbPlayers - 1)
			str = str.substr(nickLength + 1, str.size() - 1);
	}

	if(ids.size() == nicks.size())
		return true;
	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvYourId(const Message& msg, int& id)
{
	if (msg.type != Message::MessageType::SV_YOUR_ID ||
		msg.iData.find(Message::Key::SvYourID::ID) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvYourID::ID];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractClChoosesSecretRoom(const Message& msg, int& id, int& x, int& y)
{
	if (msg.iData.find(Message::Key::ClChoosesSecretRoom::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::ClChoosesSecretRoom::X) == msg.iData.end() ||
		msg.iData.find(Message::Key::ClChoosesSecretRoom::Y) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::ClChoosesSecretRoom::ID];
	x = msg.iData[Message::Key::ClChoosesSecretRoom::X];
	y = msg.iData[Message::Key::ClChoosesSecretRoom::Y];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvPlayerMoves(const Message& msg, int& id, int& x, int& y)
{
	if (msg.type != Message::MessageType::SV_MOVE ||
		msg.iData.find(Message::Key::SvMove::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvMove::X) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvMove::Y) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvMove::ID];
	x = msg.iData[Message::Key::SvMove::X];
	y = msg.iData[Message::Key::SvMove::Y];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvPlayerTakesTreasureFromPlayer(const Message& msg, int& winnerId)
{
	if (msg.type != Message::MessageType::SV_PLAYER_TAKES_TREASURE_FROM_PLAYER ||
		msg.iData.find(Message::Key::SvPlayerTakesTreasureFromPlayer::ID_WINNER) == msg.iData.end())
	{
		return false;
	}

	winnerId = msg.iData[Message::Key::SvPlayerTakesTreasureFromPlayer::ID_WINNER];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvWall(const Message& msg, int& cellX, int& cellY, Direction& direction)
{
	if (msg.type != Message::MessageType::SV_WALL ||
		msg.iData.find(Message::Key::SvWall::X) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvWall::Y) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvWall::DIRECTION) == msg.iData.end())
	{
		return false;
	}

	cellX = msg.iData[Message::Key::SvWall::X];
	cellY = msg.iData[Message::Key::SvWall::Y];
	direction = (Direction) msg.iData[Message::Key::SvWall::DIRECTION];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvConnectionResult(const Message& msg, int& result, int& error, std::string& reason)
{
	if (msg.type != Message::MessageType::SV_CONNECTION_RESULT ||
		msg.iData.find(Message::Key::SvConnectionResult::RESULT) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvConnectionResult::ERROR_CONNEC) == msg.iData.end() ||
		msg.sData.find(Message::Key::SvConnectionResult::REASON) == msg.sData.end())
	{
		return false;
	}

	result = msg.iData[Message::Key::SvConnectionResult::RESULT];
	error = msg.iData[Message::Key::SvConnectionResult::ERROR_CONNEC];
	reason = msg.sData[Message::Key::SvConnectionResult::REASON];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvSecretRoomChosen(const Message& msg, int& id, int& x, int& y)
{
	if (msg.type != Message::MessageType::SV_SECRET_ROOM_CHOSEN ||
		msg.iData.find(Message::Key::SvSecretRoomChosen::ID) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvSecretRoomChosen::X) == msg.iData.end() ||
		msg.iData.find(Message::Key::SvSecretRoomChosen::Y) == msg.iData.end())
	{
		return false;
	}

	id = msg.iData[Message::Key::SvSecretRoomChosen::ID];
	x = msg.iData[Message::Key::SvSecretRoomChosen::X];
	y = msg.iData[Message::Key::SvSecretRoomChosen::Y];

	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MessageBuilder::extractSvSendChatMessage(const Message& msg, std::string& message)
{
	if (msg.type != Message::MessageType::SV_SEND_CHAT_MESSAGE ||
		msg.sData.find(Message::Key::SvSendChatMessage::MESSAGE) == msg.sData.end())
	{
		return false;
	}

	message = msg.sData[Message::Key::SvSendChatMessage::MESSAGE];

	return true;
}