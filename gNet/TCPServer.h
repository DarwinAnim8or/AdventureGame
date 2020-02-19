#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <map>

namespace gNet {
	class TCPServer {
	public:
		TCPServer(const std::string& ip, unsigned short port, bool isBlocking = true);
		~TCPServer();

		void Update();
		bool SendPacket(const sf::Packet& packet, sf::TcpSocket* client, bool broadcast);

		sf::TcpSocket* GetClient(const std::string& ip, unsigned short port);

	private:
		sf::TcpListener mListener;
		std::map<unsigned int, sf::TcpSocket*> mClients;
		sf::IpAddress mLocalIP;
		bool mListenThreadActive = false;
	};
}
