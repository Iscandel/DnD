#pragma once
#include "Message.h"

class Game;

class MessageBuilder
{
public:
	MessageBuilder(void);
	~MessageBuilder(void);

	static Message clMovedToHand(int cardId);
	static Message SvNewPlayer(int id, int team, const std::string& name);
};