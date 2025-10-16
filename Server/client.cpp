#include <iostream>
#include <sstream>
#include <string>

#include "client.h"
#include "socket.h"

std::vector<Client> clients;

bool isClientConnected(SOCKET clientSocket) {
    char buffer;
    int result = recv(clientSocket, &buffer, 1, MSG_PEEK);
    if (result == 0) {
        return false; // Connection has been gracefully closed
	}   
    return true;
}

bool isClientInList(SOCKET clientSocket) {
    for (const auto& client : clients) {
        if (client.clientSocket == clientSocket) {
            return true;
		}   
    }
    return false;
 }

void disconnectClient(SOCKET& clientSocket) {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
    if (isClientInList(clientSocket)) {
        removeClientFromList(clientSocket);
	}
}

void removeClientFromList(SOCKET clientSocket) {
    for (auto it = clients.begin(); it != clients.end(); ) {
        if (it->clientSocket == clientSocket) {
            std::cout << "Removing client: " << it->username << " (" << it->ipAddress << ")" << std::endl;
            it = clients.erase(it);
        }
        else {
            ++it;
        }
    }
}

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
                std::string strBuffer(buffer, bytes); // Only valid bytes
                if (strBuffer.find("#clientID") != std::string::npos) {
                    std::stringstream ss(strBuffer);
                    std::vector<std::string> tokens;
                    std::string token;
                    while (std::getline(ss, token, '#')) {
                        if (!token.empty())
                            tokens.push_back(token);
                    }

                    if (tokens.size() >= 3) {
                        Client client;
                        client.clientSocket = clientSocket;
                        client.ipAddress = tokens[1];
                        client.username = tokens[2];
                        clients.push_back(client);
                        std::cout << "New client added: " << client.username << " (" << client.ipAddress << ")" << std::endl;
                    }
                }
                else {
                    broadcast(strBuffer);
                }
                std::cout << "[+] From client: " << strBuffer << std::endl;
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