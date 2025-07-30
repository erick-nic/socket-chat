#include "../include/sockets_utils.h"
#include <iostream>

int main() {
    char recv_buffer[1024];
    int recv_buffer_size = sizeof(recv_buffer);
    int i_result;
    const char* send_buff = "Server test message";
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
        std::cout << "error binding socket" << std::endl;
        cleanup_sockets();
        return 1;
    }

    i_result = listen(s_sock, SOMAXCONN);
    if (i_result == SOCKET_ERROR) {
        std::cout << "error listening on socket" << std::endl;
        cleanup_sockets();
        return 1;
    }

    socket_t c_sock = accept(s_sock, nullptr, nullptr);
    if (c_sock == INVALID_SOCKET) {
        std::cout << "error accepting client connection" << std::endl;
        cleanup_sockets();
        return 1;
    }

    i_result = recv(c_sock, recv_buffer, recv_buffer_size, 0);
    if (i_result > 0) {
        std::cout << "Received: " << recv_buffer << std::endl;
    } else {
        std::cout << "error receiving data" << std::endl;
    }

    i_result = send(c_sock, send_buff, strlen(send_buff), 0);
    if (i_result == SOCKET_ERROR) {
        std::cout << "error sending data" << std::endl;
    }
    close_socket(s_sock);
    close_socket(c_sock);
    cleanup_sockets();
    return 0;
} 