#pragma once
#include <SFML/Network.hpp>
#include <string>

namespace gNet {
	class TCPClient {
	public:
		TCPClient();
		~TCPClient();

		bool Connect(const std::string& ip, unsigned short port);
		void Disconnect();

		bool SendPacket(const sf::Packet & packet);
		sf::Packet* Update();

		const bool GetIsConnected() const { return mIsConnected; }

	private:
		sf::TcpSocket* mSocket;
		bool mIsConnected;
	};
}