#include "TCPServer.h"
#include <future>

using namespace gNet;

TCPServer::TCPServer(const std::string & ip, unsigned short port, bool isBlocking) {
	mListener.setBlocking(isBlocking);
	
	if (ip.size() == 0)
		mListener.listen(port);
	else
		mListener.listen(port, sf::IpAddress(ip));
}

TCPServer::~TCPServer() {
	for (auto& client : mClients) {
		if (client.second) {
			client.second->disconnect();
			delete client.second;
		}

		mClients.erase(client.first);
	}

	mClients.clear();
}

void gNet::TCPServer::Update() {
	//Check for new clients:
	if (!mListenThreadActive) {
		mListenThreadActive = true;

	}

	for (auto& client : mClients) {
		sf::Packet received;
		client.second->receive(received);

		//TODO: Handle the incoming packet.
	}
}

//If broadcasting to everyone, just pass nullptr for client.
bool TCPServer::SendPacket(const sf::Packet & packet, sf::TcpSocket* client, bool broadcast) {
	//If we're not broadcasting, just send our packet to the defined client.
	if (!broadcast && client) {
		auto status = client->send(packet.getData(), packet.getDataSize());
		if (status == sf::Socket::Status::Error) return false;
		return true;
	}
	
	//Send our packet to everyone, except to the provided client. 
	if (broadcast) {
		for (auto& cl : mClients) {
			if (cl.second && cl.second != client) {
				client->send(packet.getData(), packet.getDataSize());
			}
		}

		return true;
	}
	
	return false;
}

sf::TcpSocket * gNet::TCPServer::GetClient(const std::string & ip, unsigned short port) {
	for (auto& client : mClients) {
		if (!client.second) {
			auto remote = client.second->getRemoteAddress();
			auto rPort = client.second->getRemotePort();
			
			if (rPort == port && ip == remote) {
				return client.second;
				break;
			}
		}
	}
	
	return nullptr;
}
