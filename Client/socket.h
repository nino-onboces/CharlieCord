#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

extern SOCKET clientSocket;
void handleData(SOCKET clientSocket);
bool connectToServer(const char* ipAddress, int port);
void sendData(const char* data);