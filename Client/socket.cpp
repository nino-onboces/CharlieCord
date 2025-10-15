#include <iostream>
#include <thread>
#include <atomic>

#pragma comment(lib, "ws2_32")
#include "socket.h"

std::atomic<bool> shouldReconnect{false};

void sendData(SOCKET clientSocket, const char* data) {
    try {
        int sent = send(clientSocket, data, strlen(data), 0);
        if (sent == SOCKET_ERROR) {
            std::cerr << "Error sending data! " << WSAGetLastError() << std::endl;
            shouldReconnect = true;
            return;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error sending data to server! " << ex.what() << std::endl;
        shouldReconnect = true;
    }
}   

void handleData(SOCKET clientSocket) {
    try {
        char buffer;
        while (true) {
            int bytes = recv(clientSocket, &buffer, sizeof(buffer), 0);
            if (bytes > 0) {
                std::cout << "Received data: " << buffer << std::endl;
            }
            else if (bytes == 0) {
                std::cout << "Connection closed by server." << std::endl;
                shouldReconnect = true;
                break;
            }
            else {
                int error = WSAGetLastError();
                if (error == WSAEWOULDBLOCK) {
                    Sleep(100);
                    continue;
                }
                else {
                    std::cerr << "Error receiving data! " << error << std::endl;
                    shouldReconnect = true;
                    break;
                }
            }
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error handling data from server! " << ex.what() << std::endl;
        shouldReconnect = true;
    }
}

bool connectToServer(const char* ipAddress, int port) {
    while (true) {
        // Initialize WinSock
        WSADATA wsaData;
        DWORD version = MAKEWORD(2, 2);
        if (WSAStartup(version, &wsaData) != 0) {
            std::cerr << "WSAStartup failed." << std::endl;
            Sleep(1000);
            continue;
        }
        // Create Socket
        SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Socket creation failed." << std::endl;
            WSACleanup();
            Sleep(1000);
            continue;
        }
        // Set up the addr structure
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress, &addr.sin_addr);
        // Connect to server
        if (connect(clientSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            std::cerr << "Connection failed. Retrying..." << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            Sleep(1000);
            continue;
        }
        // Connection successful
        std::cout << "[+] Connected to server." << std::endl;
		sendData(clientSocket, "#clientID#127.0.0.1#charlie");
        shouldReconnect = false;
        std::thread(handleData, clientSocket).detach();

        // Wait until handleData signals to reconnect
        while (!shouldReconnect) {
            Sleep(500);
        }

        closesocket(clientSocket);
        WSACleanup();
        std::cout << "Reconnecting..." << std::endl;
        Sleep(1000); // Wait before reconnecting
    }
    return true; // This will never be reached
}