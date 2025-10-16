#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
void handleData(SOCKET clientSocket);
bool connectToServer(const char* ipAddress, int port);
void sendData(SOCKET clientSocket, const char* data);