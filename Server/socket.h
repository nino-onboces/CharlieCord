#pragma once

#include <Windows.h>

void handleClient(SOCKET clientSocket);
bool startServer(int port);

void broadcast(std::string& data);
