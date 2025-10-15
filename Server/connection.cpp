#include <thread>  
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#include "connection.h"

void handleClient(SOCKET clientSocket) {
    try {
        // Set client to non-blocking
        u_long mode = 1; // 1 for non-blocking, 0 for blocking
        if (ioctlsocket(clientSocket, FIONBIO, &mode) != 0) {
            std::cerr << "Error setting client to non-blocking! " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
        }

        char buffer[1024];
        while (true) {
            int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                std::cout << "[+] From client: " << buffer << std::endl;
            }
            if (bytes == 0) {
                std::cout << "[-] Client disconnected!" << std::endl;
                break;
            }
            else {
                continue;
            }
        }
        closesocket(clientSocket);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error handling client! " << ex.what() << std::endl;
    }
}

bool startServer(int port) {
    try {
        // Initialize WinSock
        WSADATA wsaData;
        DWORD version = MAKEWORD(2, 2);
        if (WSAStartup(version, &wsaData) != 0) {
            std::cerr << "Error initializing winsock! " << WSAGetLastError() << std::endl;
            return false;
        }

        // Create Socket
        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket! " << WSAGetLastError() << std::endl;
            WSACleanup();
            return false;
        }

        //  Set up the addr structure
        sockaddr_in addr;
        addr.sin_addr.S_un.S_addr = INADDR_ANY;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        // Bind Socket
        if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            std::cerr << "Error binding socket! " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        // Listen
        std::cout << "[+] Listening for connection..." << std::endl;
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Error listening for connection! " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return false;
        }

        // Accept connection
        while (true) {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == INVALID_SOCKET) {
                std::cerr << "Error accepting client! " << WSAGetLastError() << std::endl;
                continue;
            }

            std::cout << "[+] Client connected." << std::endl;
            std::thread(handleClient, clientSocket).detach();
        }


    }
    catch (const std::exception& ex) {
        std::cerr << "Error starting server: " << ex.what() << std::endl;
        return false;
    }
}