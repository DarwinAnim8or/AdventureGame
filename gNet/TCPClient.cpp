#include "TCPClient.h"
using namespace gNet;

TCPClient::TCPClient() {
	mSocket = new sf::TcpSocket();
}

TCPClient::~TCPClient() {
	if (mIsConnected) Disconnect();
}

bool gNet::TCPClient::Connect(const std::string & ip, unsigned short port) {
	auto status = mSocket->connect(ip, port);
	if (status == sf::TcpSocket::Status::Done) {
		mIsConnected = true;
		return true;
	}

	return false;
}

void gNet::TCPClient::Disconnect() {
	mSocket->disconnect();
	mIsConnected = false;
}

bool gNet::TCPClient::SendPacket(const sf::Packet & packet) {
	if (!mIsConnected) return false;

	auto status = mSocket->send(packet.getData(), packet.getDataSize());
	if (status == sf::TcpSocket::Status::Done) return true;

	return false;
}

sf::Packet* gNet::TCPClient::Update() {
	if (!mIsConnected) return nullptr;

	sf::Packet temp;
	mSocket->receive(temp);
	if (temp.getDataSize() > 0) {
		sf::Packet* toReturn = new sf::Packet(temp);
		return toReturn;
	}

	return nullptr;
}
