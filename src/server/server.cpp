#include <iostream>
#include "../include/server.hpp"

Server::Server() : server_socket(INVALID_SOCKET) {
    if (!init_sockets()) {
        throw std::runtime_error("Error init the server socket");
    }

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(27015);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET) {
        throw std::runtime_error("Error creating the socket");
        cleanup_sockets();
    }

    i_result = bind(server_socket, (struct sockaddr *)&service, sizeof(service));

    if (i_result == SOCKET_ERROR) {
        throw std::runtime_error("Error binding the socket");
        cleanup_sockets();
    }

    std::cout << "Socket created successfully" << std::endl;
}

Server::~Server() {
    if (server_socket != INVALID_SOCKET) {
        close_socket(server_socket);
    }
    cleanup_sockets();
}
