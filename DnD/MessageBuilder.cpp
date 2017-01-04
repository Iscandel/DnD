#include "MessageBuilder.h"

#include <sstream>

MessageBuilder::MessageBuilder(void)
{
}


MessageBuilder::~MessageBuilder(void)
{
}

Message MessageBuilder::clMovedToHand(int cardId)
{
	Message msg;

	//msg.type = Message::MessageType::CL_CARD_MOVED_TO_HAND;
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


