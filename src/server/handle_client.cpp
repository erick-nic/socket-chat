#include "../include/sockets_utils.hpp"
#include <thread>
#include <string.h>
#include <iostream>

void handle_client(socket_t c_sock) {
    char recv_buffer[1024];
    int recv_buffer_size = sizeof(recv_buffer);
    int i_result;
    const char* send_buff = "message recived";
    std::cout << "client connected using thread: [" << std::this_thread::get_id() << "]" << std::endl;
    
    do {
        memset(recv_buffer, 0, recv_buffer_size);
        i_result = recv(c_sock, recv_buffer, recv_buffer_size, 0);
        if (i_result > 0) {
            std::cout << "received message: " << recv_buffer << " from [" << std::this_thread::get_id() << "]" <<std::endl;
            i_result = send(c_sock, send_buff, strlen(send_buff), 0);
            if (i_result == SOCKET_ERROR) {
                #ifdef _WIN32
                    int error_code = WSAGetLastError();
                    std::cerr << "error sending message: " << error_code << std::endl;
                #else
                    std::cerr << "error sending message" << std::endl;
                #endif
            }
        } else if (i_result == 0) {
            std::cout << "client disconnected" << std::endl;
        } else {
            #ifdef _WIN32
                int error_code = WSAGetLastError();
                std::cerr << "error receiving message: " << error_code << std::endl;
            #else
                std::cerr << "error receiving message" << std::endl;
            #endif
        }
    } while (i_result > 0);

    close_socket(c_sock);
    std::cout << "client thread finished: [" << std::this_thread::get_id() << "]" <<std::endl;    
};
