#include "NetworkEngine.h"
#include "tools/Logger.h"
#include "GameEngine.h"
#include "MessageBuilder.h"

#include <SFML/Network.hpp>
#include <WinSock2.h>

NetworkEngine::NetworkEngine()
:myIsMulti(false)
,myIsServer(false)
,myPort(0)
,myReceptionThreadIsRunning(false)
,myConnectionThread(&NetworkEngine::th_connection, this)
,myReceptionThread(&NetworkEngine::th_reception, this)
,myIsReceptionThreadRunning(false)
{
	myAddress = sf::IpAddress("127.0.0.1");;//sf::IpAddress::GetLocalAddress();//sf::IpAddress("127.0.0.1");
	myPort = 8205;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
NetworkEngine::~NetworkEngine()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void NetworkEngine::processMessage(const Message& msg)
{
	switch(msg.type)
	{
	//case Message::MessageType::SV_PLAYER_CREATED:
	//{
	//	int id = msg.iData[Message::Key::SvPlayerCreated::ID];
	//	int tmpId = msg.iData[Message::Key::SvPlayerCreated::TMP_ID];
	//	//if(myTemporarySockets.size() == 0)
	//	//{
	//	//	ILogger::log() << "Player " << id << " created and no socket to associate...";
	//	//}
	//	//else
	//	{
	//		sf::TcpSocket* socket = NULL;
	//		std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myTemporaryIdAndSocket.cbegin();
	//		for(; it != myTemporaryIdAndSocket.end(); ++it)
	//		{
	//			if(tmpId == it->first)
	//			{
	//				socket = it->second;
	//				myTemporaryIdAndSocket.erase(it);
	//				break;
	//			}
	//		}
	//		//sf::TcpSocket* socket = myTemporarySockets.front();
	//		//myTemporarySockets.pop();
	//		myIdAndSocket.push_back(std::make_pair(id, socket));
	//		//mySockets.push_back(socket);
	//	}
	//	break;
	//}
	//case Message::MessageType::CL_CONNECTION:
	//{
	//	myNick = msg.sData[Message::Key::ClConnection::NAME];
	//	connection();
	//}
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void NetworkEngine::update()
{
	processQueue();
}

void NetworkEngine::connection()
{
	myConnectionThread.launch();
}

void NetworkEngine::reception()
{
	myReceptionThread.launch();
	myIsMulti = true;
	myIsReceptionThreadRunning = true;
}

void NetworkEngine::listen(unsigned int port)
{
	myListener.listen(port);
	reception();
	myIsServer = true;

	ILogger::log() << "Server listening on port " << port << ".\n";
}

void NetworkEngine::sendMessage(const Message& M)
{
}

void NetworkEngine::th_connection()
{
	//Message msg;

	sf::Socket::Status status = myClientSocket.connect(myAddress, myPort);
	if(status != sf::Socket::Done)
	{
		//msg = MessageBuilder::SvConnectionResult(0, WSAGetLastError());
		ILogger::log(ILogger::ERRORS) << "Error " << WSAGetLastError() << " on connection.\n";
	}
	else
	{
		//msg = MessageBuilder::SvConnectionResult(1, 0);
		//sendMessageToGame(MessageBuilder::ClConnection(myNick));

		if(!myIsReceptionThreadRunning)
		{
			reception();
		}

		mySelector.add(myClientSocket);
		mySockets.push_back(&myClientSocket);
	}

	//sendMessageToGame(msg);
}

void NetworkEngine::th_reception()
{
	//if(isServer())
	//	mySelector.add(myListener);

	//myReceptionThreadIsRunning = true;

	//while(myReceptionThreadIsRunning)
	//{
	//	if(mySelector.wait())
	//	{
	//		if(mySelector.isReady(myListener))
	//		{
	//			sf::TcpSocket* client = new sf::TcpSocket;
	//			if(myListener.accept(*client) != sf::Socket::Done)
	//			{
	//				ILogger::log(ILogger::ERRORS) << "SV : error on accept.\n ";
	//			}
	//			else
	//			{
	//				ILogger::log() << "SV : player accepted.\n";
	//			}

	//			mySelector.add(*client);
	//			this->myTemporarySockets.push(client);
	//			myTemporaryIdAndSocket.push_back(std::make_pair(createNewTmpId(), client));
	//			mySockets.push_back(client);
	//			//sendMessageToGame(MessageBuilder::ClConnection(myNick, false));

	//			if(!canAcceptNewClient())
	//			{
	//				Message msg = MessageBuilder::SvServerFull(""); //empty string ok for network ????????
	//				sf::Packet packet;
	//				packet << msg;
	//				client->send(packet);
	//				disconnectPlayer(*client);
	//			}
	//		}
	//		else
	//		{
	//			for(unsigned int i = 0; i < mySockets.size(); i++)
	//			{

	//				if(mySelector.isReady(*mySockets[i]))
	//				{
	//					sf::Packet packet;
	//					sf::Socket::Status status = mySockets[i]->receive(packet);
	//					if(status == sf::Socket::Done)
	//					{
	//						Message msg;
	//						packet >> msg;
	//						//vérifier qu'on accepte selon si on est serveur ou pas
	//						//if(msg.type == Message::MessageType::CL_CONNECTION)
	//						//{
	//						//	myTemporarySockets.push(mySockets[i]);
	//						//	if(mySockets[i]->GetRemoteAddress() == sf::IpAddress::GetLocalAddress())
	//						//		msg.iData[Message::Key::ClConnection::IS_LOCAL_CLIENT] = 1;
	//						//	else
	//						//		msg.iData[Message::Key::ClConnection::IS_LOCAL_CLIENT] = 0;
	//						//}

	//						if(isServer())
	//							modifyMessage(msg, *mySockets[i]);
	//						
	//						if(checkValidity((Message::MessageType::messageType) msg.type))
	//							sendMessageToGame(msg);
	//					}
	//					else if(status == sf::Socket::Disconnected)
	//					{
	//						disconnectPlayer(*mySockets[i]);
	//					}
	//					else
	//					{
	//						ILogger::log(ILogger::ERRORS) << "A packet has leaded to an error..\n";
	//						disconnectPlayer(*mySockets[i]);
	//					}
	//				} //end ifReady
	//			} //end for
	//		} //end if listener
	//	} //end wait
	//} //end while
}

void NetworkEngine::disconnectPlayer(sf::Socket& socket)
{
}

int NetworkEngine::createNewTmpId()
{
	static int tmpId = 0;

	return ++tmpId;
}

void NetworkEngine::modifyMessage(Message& msg, sf::TcpSocket& socket)
{
	//msg.iData[0] = getIdBySocket(&socket);
	//
	//if(msg.type == Message::MessageType::CL_CONNECTION)
	//	msg.iData[Message::Key::ClConnection::IS_LOCAL_CLIENT] = 0;
}

//bool NetworkEngine::checkValidity(Message::MessageType::messageType type)
//{
//	//if(isServer())
//	//{
//	//	switch(type)
//	//	{
//	//	//case CL_CARD_MOVED_TO_HAND: 
//	//	case Message::MessageType::SV_START_GAME:
//	//	case Message::MessageType::SV_INIT_CARDS:
//	//	case Message::MessageType::SV_NEW_PLAYER:
//	//	case Message::MessageType::SV_PLAYER_LIST:
//	//	case Message::MessageType::SV_PLAYER_YOUR_ID:
//	//		return false;
//	//	default:
//	//		return true;
//	//	}
//	//}
//
//	return true;	
//}

void NetworkEngine::sendMessageTCP(const Message& msg)
{
	sf::Packet packet;
	packet << msg;

	if(isServer())
	{
		for(unsigned int i = 0; i < mySockets.size(); i++)
		{
			if(mySockets[i]->send(packet) != sf::Socket::Done)
			{
				ILogger::log(ILogger::ERRORS) << 
					"Send(). Data not sent for player " << getIdBySocket(mySockets[i]) <<"\n";
			}
		}
	}
	else
	{
		if(myClientSocket.send(packet) != sf::Socket::Done)
		{
			ILogger::log(ILogger::ERRORS) << 
				"Send(). Data not sent.\n";
		}
	}
}

void NetworkEngine::sendMessageTCP(const Message& msg, int id)
{
	sf::Packet packet;
	packet << msg;

	std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myIdAndSocket.cbegin();
	for(; it != myIdAndSocket.end(); it++)
	{
		if( (*it).first == id)
		{
			if(it->second->send(packet) != sf::Socket::Done)
			{
				ILogger::log(ILogger::ERRORS) << 
					"Send(). Data not sent for player " << id <<"\n";
			}
			return;
		}
	}
}

int NetworkEngine::getIdBySocket(sf::Socket* socket) const 
{
	std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myTemporaryIdAndSocket.cbegin();
	for(; it != myTemporaryIdAndSocket.end(); it++)
	{
		sf::TcpSocket* sock = it->second;
		if(sock == socket)
			return it->first;
	}

	it = myIdAndSocket.cbegin();
	for(; it != myIdAndSocket.end(); it++)
	{
		sf::TcpSocket* sock = it->second;
		if(sock == socket)
			return it->first;
	}
	return 0;
}

bool NetworkEngine::canAcceptNewClient() const
{
	return true;
}