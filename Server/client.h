#pragma once
#include <Windows.h>

void handleClient(SOCKET clientSocket);
bool isClientConnected(SOCKET clientSocket);