#include "Message.h"

Message::Message(void)
{
}

Message::~Message(void)
{
}

///////////////////////////////////////////////////////////////////////////
// Vide le contenu du message
///////////////////////////////////////////////////////////////////////////
void Message::clear()
{
	type = 0;
	iData.clear();
	fData.clear();
	sData.clear();
}

//////////////////////////////////////////////////////////////////////////////
// Sérialisation du message en paquet
//////////////////////////////////////////////////////////////////////////////
void Message::toStream(sf::Packet& Packet) const
{	
	std::map<int, int>::iterator i;
	std::map<int, float>::iterator f;
	std::map<int, std::string>::iterator s;
	
	Packet << (sf::Uint32) type;

	Packet << (sf::Uint32) iData.size();
	for(i = iData.begin(); i != iData.end(); i++)
		Packet << (sf::Uint32) i->first << (sf::Uint32) i->second;
	Packet << (sf::Uint32) fData.size();
	for(f = fData.begin(); f != fData.end(); f++)
		Packet<< f->first << f->second;
	Packet << (sf::Uint32) sData.size();
	for(s = sData.begin(); s != sData.end(); s++)
		Packet << s->first << s->second;
}

//////////////////////////////////////////////////////////////////////////////
// Désérialisation du paquet en message
//////////////////////////////////////////////////////////////////////////////
void Message::fromStream(sf::Packet& Paquet, Message& msg)
{
	std::map<int, int>::iterator i;
	std::map<int, float>::iterator f;
	std::map<int, std::string>::iterator s;
	sf::Uint32 key, size;

	Paquet >> msg.type;

	Paquet >> size;
	for(sf::Uint32 i = 0; i < size; i++)
	{
		Paquet >> key;
		Paquet >> msg.iData[key];
	}
	Paquet >> size;
	for(sf::Uint32 f = 0; f < size; f++)
	{
		Paquet >> key;
		Paquet >> msg.fData[key];
	}
	Paquet >> size;
	for(sf::Uint32 s = 0; s < size; s++)
	{
		Paquet >> key;
		Paquet >> msg.sData[key];
	}
}

sf::Packet& operator << (sf::Packet& packet, const Message& msg)
{ 
    msg.toStream(packet); 
    return packet; 
} 

sf::Packet& operator >> (sf::Packet& packet, Message& msg)
{ 
    msg.fromStream(packet, msg); 
    return packet; 
} 