#include <SFML/Network.hpp>
#include <string>
#include <iostream>

#include "TCPServer.h"
#include "TCPClient.h"

using namespace gNet;

void UdpTest() {
	sf::UdpSocket server;
	sf::UdpSocket client;

	server.bind(5400);
	client.bind(5401);
	sf::IpAddress ip("localhost");

	int x = 5;
	std::string test = "Hello I am the server.";
	sf::Packet packet;
	packet << x << test << x;

	server.send(packet, ip, 5401);

	sf::Packet clientPacket;
	unsigned short senderPort = 5400;
	client.receive(clientPacket, ip, senderPort);
	int cX;
	std::string cTest;
	clientPacket >> cX;
	clientPacket >> cTest;

	std::cout << cX << cTest << std::endl;
}

void TcpTest() {
	sf::IpAddress ip("localhost");
	sf::TcpSocket servSock;
	sf::TcpListener servListener;
	servListener.setBlocking(false);

	//We wait here for new connections, then for each new connection we just make a new socket & use that to communicate.
	servListener.listen(5300); 

	sf::TcpSocket clientSock;
	clientSock.connect(ip, 5300);
	servListener.accept(servSock);

	sf::Packet servPacket;
	int x = 5;
	std::string test = "Hello I am the server.";
	servPacket << x << test;
	servSock.send(servPacket);

	sf::Packet clientPacket;
	clientSock.receive(clientPacket);
	int cX;
	std::string clientTest;
	clientPacket >> cX;
	clientPacket >> clientTest;

	std::cout << cX << clientTest << std::endl;
}

void gNetTest() {
	TCPServer server("", 1001);
	TCPClient* client = new TCPClient();
	client->Connect("localhost", 1001);

	std::cout << "Client connection state: " << int(client->GetIsConnected()) << std::endl;

	sf::Packet sc;
	sc << "test";
	server.SendPacket(sc, nullptr, true);

	auto received = client->Update();
	if (received) {
		std::string var;
		received->operator>>(var);
		std::cout << var << std::endl;
	}

	delete client;
}

int main()
{
	UdpTest();
	TcpTest();

	gNetTest();

	return 0;
}