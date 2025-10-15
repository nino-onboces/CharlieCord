#pragma once
#include <Windows.h>
#include <unordered_set>
#include <vector>

// Client Struct
struct Client {
	SOCKET clientSocket;
	std::string ipAddress;
	std::string username;
};

// Client Container 
extern std::vector<Client> clients;

void handleClient(SOCKET clientSocket);

// Checks
bool isClientConnected(SOCKET clientSocket);
bool isClientInList(SOCKET clientSocket);

void disconnectClient(SOCKET& clientSocket);
void removeClientFromList(SOCKET clientSocket);
