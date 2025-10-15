#include <iostream>

#include "socket.h"
int main() {
	connectToServer("127.0.0.1", 9999);
	std::cout << "Test client for CharlieCord" << std::endl;
}