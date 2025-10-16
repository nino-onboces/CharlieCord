#include <iostream>
#include <string>
#include <thread>

#include "functions.h"
#include "socket.h"

void connect() {
    std::thread(connectToServer, "127.0.0.1", 9999).detach();
}

int main() {
    std::cout << "  /$$$$$$  /$$                           /$$ /$$            /$$$$$$                            /$$\n /$$__  $$| $$                          | $$|__/           /$$__  $$                          | $$\n| $$  \\__/| $$$$$$$   /$$$$$$   /$$$$$$ | $$ /$$  /$$$$$$ | $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$$\n| $$      | $$__  $$ |____  $$ /$$__  $$| $$| $$ /$$__  $$| $$       /$$__  $$ /$$__  $$ /$$__  $$\n| $$      | $$  \\ $$  /$$$$$$$| $$  \\__/| $$| $$| $$$$$$$$| $$      | $$  \\ $$| $$  \\__/| $$  | $$\n| $$    $$| $$  | $$ /$$__  $$| $$      | $$| $$| $$_____/| $$    $$| $$  | $$| $$      | $$  | $$\n|  $$$$$$/| $$  | $$|  $$$$$$$| $$      | $$| $$|  $$$$$$$|  $$$$$$/|  $$$$$$/| $$      |  $$$$$$$\n \\______/ |__/  |__/ \\_______/|__/      |__/|__/ \\_______/ \\______/  \\______/ |__/       \\_______/\n\n";
    std::string input_main;
    std::string username = "default_user01";
    std::string user_color = "WHITE";

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
            std::cout << "\033[31mThis text is red.\033[0m\n";
            std::cout << "'settings' - configure YOUR terminal.\n";
            std::cout << "'end'  - End program.\n\n";

        }
        else if (input_main == "connect") {
            connect();
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