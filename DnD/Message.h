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
	struct MessageType
	{
		enum messageType
		{		
			CL_MOVE,
			CL_DRAGOON_MOVES,
			CL_DRAGOON_AWAKES,
			CL_PLAYER_LOOSES,
			CL_PLAYER_WOUNDED,
			CL_END_TURN,
			SV_DRAGOON_AWAKES,
			SV_MOVE,
			SV_WALL,
			PLAY_SOUND,
			PLAY_MUSIC,
			STOP_MUSIC,
			SV_MAZE,
			SV_NEW_TURN,
			SV_DRAGOON_MOVES,
			SV_TAKE_TREASURE,
			SV_PLAYER_TAKES_TREASURE_FROM_PLAYER,
			SV_GAME_WON,
			SV_PLAYER_WOUNDED,
			SV_PLAYER_LOOSES
		};
	};

	//All the keys associated to messages
	struct Key
	{
		struct ExampleLoadGame {
			//sData map key
			enum {
				GAME_NAME
			};
		};

		struct clMove {
			enum {
				ID,			//iData, filled par server for distant players
				DIRECTION,  //iData, enum
			};
		};

		struct clDragoonMoves {
			enum {
				ID,			//iData
				DIRECTION_HORIZ,  //iData, enum
				DIRECTION_VERT,  //iData, enum
			};
		};

		struct clPlayerLooses {
			enum {
				ID,			//iData
			};
		};

		struct ClEndTurn { //Special sent by server to server...to change, maybe
			enum {
				ID,			//iData
			};
		};

		struct clPlayerWounded {
			enum {
				ID,			//iData
			};
		};

		struct SvMove {
			enum {
				ID,
				X,
				Y
			};
		};

		struct SvWall {
			enum {
				X,
				Y,
				DIRECTION
			};
		};

		struct SvPlayerTakesTreasureFromPlayer {
			enum {
				ID_WINNER, //iData
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

		struct SvTakeTreasure {
			enum {
				ID, //iData
			};
		};

		struct SvGameWon {
			enum {
				ID, //iData
			};
		};

		struct SvNewTurn {
			enum {
				ID, //iData
			};
		};

		struct SvPlayerWounded {
			enum {
				ID, //iData
				NUMBER_LIVES //iData
			};
		};

		struct SvPlayerLooses {
			enum {
				ID, //iData
			};
		};

		struct PlaySound {
			enum {
				ID_SOUND, //sData
			};
		};
	};
};

#endif