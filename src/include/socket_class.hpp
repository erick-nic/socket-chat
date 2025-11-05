#pragma once
#include "../include/socket/sockets_utils.hpp"
#include <stdexcept>
#include <iostream>

class Server {
private:
    int i_result;
    struct sockaddr_in service;
    socket_t s_socket;

public:
    Server();    
    ~Server(); 

    socket_t s_accept();
};  
