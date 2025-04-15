#include <iostream>
#include <winsock2.h>
#include "../shared/shared.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main() {
	WSADATA wsa;
	SOCKET serverSocket, clientSocket;
	struct sockaddr_in server, client;
	char buffer[1024] = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsa);
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(12345);

	bind(serverSocket, (struct sockaddr*)&server, sizeof(server));
	listen(serverSocket, 3);

	int c = sizeof(struct sockaddr_in);
	clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);

	while (true) {
		int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (recvLen <= 0) break;

		Message msg = Message::deserialize(std::string(buffer, recvLen));
		std::cout << "Client says: " << msg.text << std::endl;

		std::string response = msg.serialize(); // Echo
		send(clientSocket, response.c_str(), response.size(), 0);
	}

	std::cout << "bye" << std::endl;

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
