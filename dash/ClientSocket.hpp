//
//  ClientSocket.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef ClientSocket_cpp
#define ClientSocket_cpp

#include <iostream>
#include <string>
#include <sstream>

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#include <termios.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#elif _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <fcntl.h>

#include "SocketException.h"

#include <sys/types.h>
#include <cstdint>
#include <string.h>

#include "Definitions.h"

using std::string;

class ClientSocket
{
private:
    
    int _sockfd;
    bool _ready;
    char *_buffer;
    void _connect();

    std::string _host;
    unsigned int _port;
    unsigned int _buffer_size;
    int _wait_timeout;
    
public:
    ClientSocket(string host, unsigned int port, unsigned int buffer_len, int wait_timeout);

    ~ClientSocket();

    void connectSocket();
    void send_server(sock_msg_t message);

    sock_msg_t checkForIncomingMessages();

    unsigned int getBufferSize();
    bool isReady();
};

#endif /* ClientSocket_cpp */
