#include <iostream>
#include <winsock2.h>
#include <string>
#include "../shared/shared.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main() {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in server;
	char buffer[1024] = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsa);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);

	connect(sock, (struct sockaddr*)&server, sizeof(server));

	std::cout << "hello" << std::endl;

	while (true) {
		std::string input;
		std::cout << "Input: ";
		std::getline(std::cin, input);

		if (input == "exit") break;

		Message msg{ input };
		std::string data = msg.serialize();
		send(sock, data.c_str(), data.size(), 0);

		int recvLen = recv(sock, buffer, sizeof(buffer), 0);
		if (recvLen > 0) {
			Message response = Message::deserialize(std::string(buffer, recvLen));
			std::cout << "Echo: " << response.text << std::endl;
		}
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
