#include "../include/sockets_utils.h"
#include "../include/handle_client.h"
#include <iostream>
#include <vector>

int main() {
    int i_result;
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(27015);
    
    if (!init_sockets()) {
        #ifdef _WIN32
            std::cout << WSAGetLastError();
        #else
            std::cerr << "Failed to initialize sockets" << std::endl;
            std::cerr << "Error: " << strerror(errno) << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }
    
    socket_t s_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s_sock == INVALID_SOCKET) {
        #ifdef _WIN32
            int error_code = WSAGetLastError();
            std::cerr << "error creating socket: " << error_code << "";
        #else
            std::cout << "error creating socket" << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }
    std::cout << "socket created successfully" << std::endl;
    i_result = bind(s_sock, (struct sockaddr*)&service, sizeof(service));
    if (i_result == SOCKET_ERROR) {
        #ifdef _WIN32
            int error_code = WSAGetLastError();
            std::cerr << "error binding socket: " << error_code << "";
        #else
            std::cerr << "error binding socket" << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }

    i_result = listen(s_sock, SOMAXCONN);
    if (i_result == SOCKET_ERROR) {
        #ifdef _WIN32 
            int error_code = WSAGetLastError();
            std::cerr << "error listening on socket: " << error_code << "";
        #else
            std::cout << "error listening on socket" << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }

    while (true) {
        socket_t c_sock = accept(s_sock, nullptr, nullptr);
        if (c_sock == INVALID_SOCKET) {
            #ifdef _WIN32
                int error_code = WSAGetLastError();
                std::cerr << "error accepting client connection" << error_code << std::endl;
            #else    
                std::cerr << "error accepting client connection" << std::endl;
            #endif
            cleanup_sockets();
            return 1;
        }

        std::thread c_thread(handle_client, c_sock);
        c_thread.detach();
    }
    close_socket(s_sock);
    cleanup_sockets();
    return 0;
} 