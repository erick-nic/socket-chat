
#include "../include/sockets_utils.hpp"
#include <stdexcept>
#include <iostream>
#pragma once

class Server {
private:
    int i_result;
    struct sockaddr_in service;
    socket_t server_socket;

public:
    Server();    
    ~Server(); 
};  
