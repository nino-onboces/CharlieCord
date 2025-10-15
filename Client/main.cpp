#include <iostream>
#include <string>
#include <thread>

#include "functions.h"
#include "socket.h"

std::string input_main;
std::string username = "default_user01";
std::string user_color = "WHITE";
std::string server_ip = "10.128.238.176";
int server_port = 9999;

void connect(std::string &ip, int port, std::string &username) {
    std::thread(connectToServer, std::ref(ip), port, std::ref(username)).detach();
}

int main() {
    std::cout << "  /$$$$$$  /$$                           /$$ /$$            /$$$$$$                            /$$\n /$$__  $$| $$                          | $$|__/           /$$__  $$                          | $$\n| $$  \\__/| $$$$$$$   /$$$$$$   /$$$$$$ | $$ /$$  /$$$$$$ | $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$$\n| $$      | $$__  $$ |____  $$ /$$__  $$| $$| $$ /$$__  $$| $$       /$$__  $$ /$$__  $$ /$$__  $$\n| $$      | $$  \\ $$  /$$$$$$$| $$  \\__/| $$| $$| $$$$$$$$| $$      | $$  \\ $$| $$  \\__/| $$  | $$\n| $$    $$| $$  | $$ /$$__  $$| $$      | $$| $$| $$_____/| $$    $$| $$  | $$| $$      | $$  | $$\n|  $$$$$$/| $$  | $$|  $$$$$$$| $$      | $$| $$|  $$$$$$$|  $$$$$$/|  $$$$$$/| $$      |  $$$$$$$\n \\______/ |__/  |__/ \\_______/|__/      |__/|__/ \\_______/ \\______/  \\______/ |__/       \\_______/\n\n";
    while (true) {
        std::cout << "[+] Enter command: ";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> input_main; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        if (input_main == "end") {
            setCursorVisible(false);
            for (int i = 0; i < 3; i++) {
                std::cout << "Exiting program.  ";
                moveCursor(0, getCursorY());
                Sleep(250);
                std::cout << "Exiting program.. ";
                moveCursor(0, getCursorY());
                Sleep(250);
                std::cout << "Exiting program...";
                moveCursor(0, getCursorY());
                Sleep(250);
            }
            std::cout << "\n";
            break;
        }

        else if (input_main == "help") {
            std::cout << "Here is a list of available commands:\n";
            std::cout << "'help' - Show all available commands.\n";
            std::cout << "'connect' - Connect to server with specified port.";
            std::cout << "'settings' - configure YOUR terminal.\n";;
            std::cout << "'end'  - End program.\n\n";

        }
        else if (input_main == "connect") {
            connect(server_ip, server_port, username);
            std::string serverInput;
            while (true) {
                std::cout << "> ";
                std::getline(std::cin, serverInput);
                
                sendData(serverInput.c_str());

                if (serverInput == "disconnect") {
                    break;
                }
            }
        }
        else if (input_main == "settings") {
            std::cout << "'color' - changes username color.\n";
            std::cout << "'username' - change username.\n";

            std::cout << "'back' = return to main screen.\n\n";

            std::string input_settings;
            while (true) {
                std::cout << "<settings> [+] Enter command: ";
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> input_settings; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                if (input_settings == "color") {
                    std::cout << "<settings> [+] What color do you want: ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> user_color; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                }
                else if (input_settings == "username") {
                    std::cout << "<settings> [+] Enter a new username: ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> username; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    std::cout << "Changed username to " << username << "\n\n";
                }
                else if (input_settings == "ip") {
                    std::cout << "<settings> [+] Enter the IP address of your desired server: ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> server_ip; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    std::cout << "Changed server IP address to " << username << "\n\n";
                }
                else if (input_settings == "username") {
                    std::cout << "<settings> [+] Enter the port of your desired server: ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); std::cin >> server_port; std::cout << "\n"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    std::cout << "Changed server port to " << username << "\n\n";
                }
                else if (input_settings == "back") {
                    break;
                }
                else {
                    std::cout << "Invalid command.\n";
                    continue;
                }
            }
        }
        else {
            std::cout << "Invalid command.\n";
            continue;
        }
    }



    return 0;
};