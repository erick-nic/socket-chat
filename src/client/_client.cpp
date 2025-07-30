#include "../include/sockets_utils.h"
#include <iostream>

int main () {
    char recv_buffer[1024];
    int recv_buffer_size = sizeof(recv_buffer);
    int i_result;
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.100.3", &service.sin_addr.s_addr);
    service.sin_port = htons(27015);
    std::string message;

    if (!init_sockets()) {
        #ifdef _WIN32
            std::cout << WSAGetLastError();
            std::cerr << "Failed to initialize sockets" << std::endl;
        #else
            std::cerr << "Failed to initialize sockets" << std::endl;
            std::cerr << "Error: " << strerror(errno) << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }

    socket_t c_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c_sock == INVALID_SOCKET) {
        #ifdef _WIN32
            int error_code = WSAGetLastError();
            std::cerr << "error creating sockets: " << error_code << std::endl;
        #else
            std::cerr << "error creating sockets" << std::endl;
        #endif
        cleanup_sockets();
        return 1;
    }

    std::cout << "socket created successfully" << "\n";
    std::cout << "trying to connect to server..." << std::endl;
    i_result = connect(c_sock, (struct sockaddr*)&service, sizeof(service));
    if (i_result == SOCKET_ERROR) {
        #ifdef _WIN32
            int error_code = WSAGetLastError();
            std::cerr << "error connecting to server: " << error_code << std::endl;
        #else
            std::cerr << "error connecting to server" << std::endl;
        #endif
        close_socket(c_sock);
        cleanup_sockets();
        return 1;
    }   

    std::cout << "connected to server, type exit to close..." << std::endl;
    do {
        std::cout << "type a message..." << std::endl;
        std::getline(std::cin, message);
        if (message == "exit") {
            break;
        }
        i_result = send(c_sock, message.c_str(), (int)message.length(), 0);
        if (i_result == SOCKET_ERROR) {
            #ifdef _WIN32
                int error_code = WSAGetLastError();
                std::cerr << "error sending message: " << error_code << std::endl;
                break;
            #else
                std::cerr << "error sending message" << std::endl;
                break;
            #endif
        }

        i_result = recv(c_sock, recv_buffer, recv_buffer_size, 0);
        if (i_result > 0) {
            recv_buffer[i_result] = '\0';
            std::cout << "servidor: " << recv_buffer << std::endl;
        } else if (i_result == 0) {
            std::cout << "connection closed by the server" << std::endl;
            break;
        } else {
            #ifdef _WIN32 
                std::cerr << "error recv response" << WSAGetLastError() << std::endl;
                break;
            #else
                std::cerr << "error recv responde" << std::endl;
                break;
            #endif
        }
    } while (true);
    close_socket(c_sock);
    cleanup_sockets();
    return 0;
}   