#ifndef H_MESSAGE_150820130123_H
#define H_MESSAGE_150820130123_H

#include <iostream>
#include <map>
//#include <SFML/System.hpp>
#include <SFML/Network.hpp>

///////////////////////////////////////////////////////////////////////////////
/// \brief Class representing a message with different data types.
///////////////////////////////////////////////////////////////////////////////
class Message
{
public:
	Message(void);
	~Message(void);

	friend sf::Packet& operator << (sf::Packet& Packet, const Message& M); 
	friend sf::Packet& operator >> (sf::Packet& Packet, Message& M); 
	
	///////////////////////////////////////////////////////////////////////////
	// Vide le contenu du message
	///////////////////////////////////////////////////////////////////////////
	void clear();

	//Message data
	mutable std::map<int, int> iData;
	mutable std::map<int, float> fData;
	mutable std::map<int, std::string> sData;

protected:
	//////////////////////////////////////////////////////////////////////////////
	// Sérialise (?) le contenu d'un message dans un paquet 
	//////////////////////////////////////////////////////////////////////////////
	void toStream(sf::Packet& Packet)const;

	//////////////////////////////////////////////////////////////////////////////
	// Extrait le contenu d'un paquet vers un message
	//////////////////////////////////////////////////////////////////////////////
	void fromStream(sf::Packet& Packet, Message& M);
	
public:
	int type;

	//struct MessageType
	//{
	//	enum messageType
	//	{							
	//		EXAMPLE_1,
	//		EXAMPLE_2
	//	};
	//};
	//struct MessageType
	//{
	//	enum messageType
	//	{							
	//	};
	//};

	//All the keys associated to messages
	struct Key
	{
		struct ExampleLoadGame {
			//sData map key
			enum {
				GAME_NAME
			};
		};

		struct SvNewPlayer {
			enum {
				ID,   //iData
				TEAM, //iData
				NAME  //sData
			};
		};

		struct SvPlayerList {
			enum {
				NB_PLAYERS, //iData
				LIST //sData (id, team, nicklength, nick)
			};
		};

		struct ClConnection {
			enum {
				TMP_ID, //iData
				NAME, //sData
				IS_LOCAL_CLIENT, //iData (0 or 1)
			};
		};

		struct SvPlayerCreated {
			enum {
				ID, //iData
				TMP_ID //iData
			};
		};

		struct SvConnectionResult {
			enum {
				RESULT, //iData
				ERROR_CONNEC, //iData
			};
		};

		struct SvServerFull {
			enum {
				INFO, //sData
			};
		};
	};
};

#endif