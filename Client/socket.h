#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>

extern SOCKET clientSocket;
void handleData(SOCKET clientSocket);
bool connectToServer(const std::string &ipAddress, int port, const std::string &username);
void sendData(const std::string &data);