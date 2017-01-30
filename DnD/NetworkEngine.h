#ifndef H__NETWORKENGINE_160820130116_H
#define H__NETWORKENGINE_160820130116_H

#include "Engine.h"

#include <list>

///////////////////////////////////////////////////////////////////////////////
/// \brief Class handling the network part.
///////////////////////////////////////////////////////////////////////////////
class NetworkEngine : public Engine
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// Constructor.
	///////////////////////////////////////////////////////////////////////////
	NetworkEngine(void);

	///////////////////////////////////////////////////////////////////////////
	/// Destructor.
	///////////////////////////////////////////////////////////////////////////
	~NetworkEngine(void);

	///////////////////////////////////////////////////////////////////////////
	/// Processes a message.
	///
	/// \param msg The message to process.
	///////////////////////////////////////////////////////////////////////////
	virtual void processMessage(const Message& msg);

	///////////////////////////////////////////////////////////////////////////
	/// Updates the network engine. 
	///////////////////////////////////////////////////////////////////////////
	void update();

	void sendMessage(const Message& Msg);

	bool isMulti() {return myIsMulti;}

	bool isServer() {return myIsServer;}

	void listen(unsigned int port);

	void th_reception();

	void th_connection();

	void disconnectPlayer(sf::Socket& socket);

	//bool isRunning() const {return myReception

	void modifyMessage(Message& msg, sf::TcpSocket& socket);

	//bool checkValidity(Message::MessageType::messageType type);

	void sendMessageTCP(const Message& msg);

	void sendMessageTCP(const Message& msg, int id);

	int getIdBySocket(sf::Socket* socket) const;

	void connection();

	void reception();

	bool canAcceptNewClient() const;

	int createNewTmpId();

protected:
	bool myIsMulti;
	bool myIsServer;

	bool myIsReceptionThreadRunning;

	std::string myIP;
	sf::IpAddress myAddress;
	unsigned int myPort;
	std::string myNick;

	sf::TcpSocket myClientSocket;
	std::vector<sf::TcpSocket*> mySockets;
	sf::TcpListener myListener;
	sf::SocketSelector mySelector;

	sf::Thread myConnectionThread;
	sf::Thread myReceptionThread;

	std::queue<sf::TcpSocket*> myTemporarySockets;
	std::list<std::pair<int, sf::TcpSocket*> > myIdAndSocket;
	std::list<std::pair<int, sf::TcpSocket*> > myTemporaryIdAndSocket;

	bool myReceptionThreadIsRunning;

};

//classe ServerReseau à qui on envoie directement les messages si non connecté. 
//Sinon, on les envoie par le réseau, et le thread de réception du serveur reforwarde au ServeurReseau

#endif