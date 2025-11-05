#include <iostream>
#include "../include/socket_class.hpp"

Server::Server(): s_socket(INVALID_SOCKET) {
    if (!init_sockets()) {
        throw std::runtime_error("Error init the server socket");
    }

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(27015);
    s_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (s_socket == INVALID_SOCKET) {
        throw std::runtime_error("Error creating the socket");
        cleanup_sockets();
    }

    i_result = bind(s_socket, reinterpret_cast<sockaddr*>(&service), sizeof(service));

    if (i_result == SOCKET_ERROR) {
        throw std::runtime_error("Error binding the socket");
        cleanup_sockets();
    }

    std::cout << "Socket created successfully" << std::endl;
}

Server::~Server() {
    if (s_socket != INVALID_SOCKET) {
        close_socket(s_socket);
    }
    cleanup_sockets();
}

socket_t s_accept() {

}
