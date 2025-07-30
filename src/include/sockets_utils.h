#pragma once

#ifdef _WIN32
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <winerror.h>
    #include <string>
    #pragma comment(lib, "ws2_32.lib")
    using socket_t = SOCKET;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <cstring>
    #include <string>
    using socket_t = int;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR   -1
#endif

inline bool init_sockets() {
    #ifdef _WIN32
        WSADATA wsaData;
        return (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0);
    #else
        return true;
    #endif
}

inline void cleanup_sockets() {
    #ifdef _WIN32
        WSACleanup();
    #endif
}

inline void close_socket(socket_t sock) {
    #ifdef _WIN32
        closesocket(sock);
    #else
        close(sock);
    #endif
}
