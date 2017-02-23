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
,myIP("127.0.0.1")
,myReceptionThreadIsRunning(false)
,myConnectionThread(&NetworkEngine::th_connection, this)
,myReceptionThread(&NetworkEngine::th_reception, this)
,myIsReceptionThreadRunning(false)
{
	myAddress = sf::IpAddress(myIP);;//sf::IpAddress::GetLocalAddress();//sf::IpAddress("127.0.0.1");
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
	case Message::MessageType::CONNECTION:
	{
		if (!MessageBuilder::extractConnection(msg, myIP, myNick))
			return;

		myAddress = sf::IpAddress(myIP);
		connection();
	}
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
	myIsMulti = true;
	myIsServer = true;

	ILogger::log() << "Server listening on port " << port << ".\n";
}

//void NetworkEngine::sendMessage(const Message& M)
//{
//}

void NetworkEngine::th_connection()
{
	sf::Socket::Status status = myClientSocket.connect(myAddress, myPort);
	if(status != sf::Socket::Done)
	{
		Message msg = MessageBuilder::svConnectionResult(0, WSAGetLastError(), "Error when connecting.");
		ILogger::log(ILogger::ERRORS) << "Error " << WSAGetLastError() << " on connection.\n";
		sendMessageToGame(msg);
	}
	else
	{
		ILogger::log() << "Connected.\n";
		//msg = MessageBuilder::svConnectionResult(1, 0);
		//sendMessageToGame(MessageBuilder::ClConnection(myNick));

		if(!myIsReceptionThreadRunning)
		{
			reception();
		}
		
		Message msg = MessageBuilder::clConnection(myNick);
		sendMessageTCP(msg);
		mySelector.add(myClientSocket);
		mySockets.push_back(&myClientSocket);
	}	
}

void NetworkEngine::th_reception()
{
	if(isServer())
		mySelector.add(myListener);

	myReceptionThreadIsRunning = true;

	while(myReceptionThreadIsRunning)
	{
		if(mySelector.wait())
		{
			if(mySelector.isReady(myListener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if(myListener.accept(*client) != sf::Socket::Done)
				{
					ILogger::log(ILogger::ERRORS) << "SV : error on accept.\n ";
				}
				else
				{
					ILogger::log() << "SV : player accepted.\n";
				}

				mySelector.add(*client);
				//this->myTemporarySockets.push(client);
				myTemporaryIdAndSocket.push_back(std::make_pair(createNewTmpId(), client));
				mySockets.push_back(client);

				if(!canAcceptNewClient())
				{
					//Message msg = MessageBuilder::SvServerFull(""); //empty string ok for network ????????
					//sf::Packet packet;
					//packet << msg;
					//client->send(packet);
					//disconnectPlayer(*client);
				}
			}
			else
			{
				for(unsigned int i = 0; i < mySockets.size(); i++)
				{

					if(mySelector.isReady(*mySockets[i]))
					{
						sf::Packet packet;
						sf::Socket::Status status = mySockets[i]->receive(packet);
						if(status == sf::Socket::Done)
						{
							Message msg;
							packet >> msg;

							//vérifier qu'on accepte selon si on est serveur ou pas
							//if(msg.type == Message::MessageType::CL_CONNECTION)
							//{
							//	myTemporarySockets.push(mySockets[i]);
							//	if(mySockets[i]->GetRemoteAddress() == sf::IpAddress::GetLocalAddress())
							//		msg.iData[Message::Key::ClConnection::IS_LOCAL_CLIENT] = 1;
							//	else
							//		msg.iData[Message::Key::ClConnection::IS_LOCAL_CLIENT] = 0;
							//}

							if(isServer())
								modifyMessage(msg, *mySockets[i]);

							sendMessageToGame(msg);
							
							//if(checkValidity((Message::MessageType::messageType) msg.type))
							//	sendMessageToGame(msg);
						}
						else if(status == sf::Socket::Disconnected)
						{
							disconnectPlayer(mySockets[i]);
						}
						else
						{
							ILogger::log(ILogger::ERRORS) << "A packet has leaded to an error..\n";
							disconnectPlayer(mySockets[i]);
						}
					} //end ifReady
				} //end for
			} //end if listener
		} //end wait
	} //end while
}

void NetworkEngine::disconnectPlayer(int id, bool temporary)
{
	sf::TcpSocket* socket = getSocketById(id, temporary);
	disconnectPlayer(socket);
}

void NetworkEngine::disconnectPlayer(sf::TcpSocket* socket)
{
	mySelector.remove(*socket);
	std::vector<sf::TcpSocket*>::iterator itSocks = mySockets.begin();
	for (; itSocks != mySockets.end();)
	{
		if (*itSocks == socket)
			itSocks = mySockets.erase(itSocks);
		else
		{
			++itSocks;
		}
	}

	std::list<std::pair<int, sf::TcpSocket*> >::iterator it = myTemporaryIdAndSocket.begin();
	for (; it != myTemporaryIdAndSocket.end(); )
	{
		sf::TcpSocket* sock = it->second;
		if (sock == socket)
			it = myIdAndSocket.erase(it);
		else
			++it;
	}

	it = myIdAndSocket.begin();
	for (; it != myIdAndSocket.end();)
	{
		sf::TcpSocket* sock = it->second;
		if (sock == socket)
			it = myIdAndSocket.erase(it);
		else
			++it;
	}
}

int NetworkEngine::createNewTmpId()
{
	static int tmpId = 0;

	return ++tmpId;
}

void NetworkEngine::modifyMessage(Message& msg, sf::TcpSocket& socket)
{
	msg.iData[0] = getIdBySocket(&socket);
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

	if (isMulti())
	{
		if (isServer())
		{
			for (unsigned int i = 0; i < mySockets.size(); i++)
			{
				if (mySockets[i]->send(packet) != sf::Socket::Done)
				{
					ILogger::log(ILogger::ERRORS) <<
						"Send(). Data not sent for player " << getIdBySocket(mySockets[i]) << "\n";
				}
			}
		}
		else
		{
			if (myClientSocket.send(packet) != sf::Socket::Done)
			{
				ILogger::log(ILogger::ERRORS) <<
					"Send(). Data not sent.\n";
			}
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

void NetworkEngine::sendMessageTCPToAllExcept(const Message& msg, int id)
{
	std::vector<int> vec;
	vec.push_back(id);
	sendMessageTCPToAllExcept(msg, vec);
}

void NetworkEngine::sendMessageTCPToAllExcept(const Message& msg, const std::vector<int>& ids)
{
	sf::Packet packet;
	packet << msg;

	for (unsigned int i = 0; i < mySockets.size(); i++)
	{
		bool dontSend = false;
		int id = getIdBySocket(mySockets[i]);
		
		for (int excl : ids)
		{
			if (excl == id)
				dontSend = true;
		}
		if (!dontSend)
		{
			if (mySockets[i]->send(packet) != sf::Socket::Done)
			{
				ILogger::log(ILogger::ERRORS) <<
					"Send(). Data not sent for player " << getIdBySocket(mySockets[i]) << "\n";
			}
		}
	}
}

int NetworkEngine::getIdBySocket(sf::Socket* socket) const 
{
	std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myTemporaryIdAndSocket.cbegin();
	for(; it != myTemporaryIdAndSocket.cend(); it++)
	{
		sf::TcpSocket* sock = it->second;
		if(sock == socket)
			return it->first;
	}

	it = myIdAndSocket.cbegin();
	for(; it != myIdAndSocket.cend(); it++)
	{
		sf::TcpSocket* sock = it->second;
		if(sock == socket)
			return it->first;
	}
	return 0;
}

void NetworkEngine::changeTemporaryToFinal(int tmpId, int finalId)
{
	sf::TcpSocket* candidate = nullptr;

	std::list<std::pair<int, sf::TcpSocket*> >::iterator it = myTemporaryIdAndSocket.begin();
	for (; it != myTemporaryIdAndSocket.end(); it++)
	{
		if (it->first == tmpId)
		{
			candidate = it->second;
			myTemporaryIdAndSocket.erase(it);
			break;
		}
	}

	myIdAndSocket.push_back(std::make_pair(finalId, candidate));
}

sf::TcpSocket* NetworkEngine::getSocketById(int id, bool isTemporary)
{
	sf::TcpSocket* candidate = nullptr;

	if(isTemporary)
	{
		std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myTemporaryIdAndSocket.cbegin();
		for (; it != myTemporaryIdAndSocket.end(); it++)
		{
			if (it->first == id)
			{
				candidate = it->second;
				break;
			}
		}
	}
	else
	{
		std::list<std::pair<int, sf::TcpSocket*> >::const_iterator it = myIdAndSocket.cbegin();
		for (; it != myIdAndSocket.end(); it++)
		{
			if (it->first == id)
			{
				candidate = it->second;
				break;
			}
		}
	}

	return candidate;
}

bool NetworkEngine::canAcceptNewClient() const
{
	return true;
}