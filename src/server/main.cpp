#include "../include/server.hpp"
#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    try {
        Server socket_server;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        
        return -1;
    };
 
    // i_result = listen(s_sock, SOMAXCONN);
    // if (i_result == SOCKET_ERROR) {
    //     #ifdef _WIN32 
    //         int error_code = WSAGetLastError();
    //         std::cerr << "error listening on socket: " << error_code << "";
    //     #else
    //         std::cout << "error listening on socket" << std::endl;
    //     #endif
    //     cleanup_sockets();
    //     return 1;
    // }

    // while (true) {
    //     socket_t c_sock = accept(s_sock, nullptr, nullptr);
    //     if (c_sock == INVALID_SOCKET) {
    //         #ifdef _WIN32
    //             int error_code = WSAGetLastError();
    //             std::cerr << "error accepting client connection" << error_code << std::endl;
    //         #else    
    //             std::cerr << "error accepting client connection" << std::endl;
    //         #endif
    //         cleanup_sockets();
    //         return 1;
    //     }

    //     std::thread c_thread(handle_client, c_sock);
    //     c_thread.detach();
    // }
    // close_socket(s_sock);
  
    return 0;
} 