#include "socket_class.hpp"
#include <iostream>

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    try {
        Server socket_server;
        socket_server.s_listen();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        
        return -1;
    };
  
    return 0;
}