#include <iostream>

#include "client.h"

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