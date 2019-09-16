//
//  ClientSocket.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "ClientSocket.hpp"

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
struct termios orig_termios;
struct termios new_termios;
#endif

ClientSocket::ClientSocket(std::string host, unsigned int port, unsigned int buffer_size, int wait_timeout) :
    _host(host),
    _port(port),
    _buffer_size(buffer_size),
    _wait_timeout(wait_timeout),
    _ready(false) {
    _buffer = new char[_buffer_size];

}

ClientSocket::~ClientSocket() {
#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
    close(_sockfd);
#elif _WIN32
    closesocket(sockfd);
#endif
    
    delete _buffer;
}

void ClientSocket::connectSocket() {
    try {
        _connect();
        _ready = true;
    }
    catch(SocketException e) {
        _ready = false;
        throw std::move(e);
    }
}

void ClientSocket::_connect()
{
    struct addrinfo *result, *rp;
    struct protoent* tcp;
    struct addrinfo hints;
    int s;

    tcp = getprotobyname("tcp");
    
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = tcp->p_proto;
    
    std::stringstream l_port;
    l_port << _port;
    
    s = getaddrinfo(_host.c_str(), l_port.str().c_str(), &hints, &result);
    if (s != 0) {
        SocketException e("getaddrinfo() failed\n");
        throw e;
    }
    
    int res = -1;
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        _sockfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (_sockfd == -1) {
            continue;
        }
        
        res = connect(_sockfd, rp->ai_addr, rp->ai_addrlen);
        if (res != -1) {
            break;
        }
        
        close(_sockfd);
    }
    
    if (rp == NULL) {
        SocketException e("Failed to connect\n");
        throw e;
    }
    
    freeaddrinfo(result);
    
    struct timeval tv;
    fd_set myset;
    socklen_t lon;
    int valopt;

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
    if (res < 0) {
        if (errno == EINPROGRESS) {
            do {
                tv.tv_sec = _wait_timeout;
                tv.tv_usec = 0;
                FD_ZERO(&myset);
                FD_SET(_sockfd, &myset);
                res = select(_sockfd+1, NULL, &myset, NULL, &tv);
#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
                if (res < 0 && errno != EINTR) {
#elif _WIN32
                if (res == SOCKET_ERROR) {
#endif
                    close(_sockfd);
                    SocketException e("Error connecting!");
                    throw e;
                } else if (res > 0) {
                    // Socket selected for write
                    lon = sizeof(int);
                    if (getsockopt(_sockfd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon) < 0) {
                        close(_sockfd);
                        SocketException e("Error in getsockopt()\n");
                        throw e;
                    }
                    if (valopt) {
                        close(_sockfd);
                        SocketException e("Valopt indicating error\n");
                        throw e;
                    }
                    break;
                } else {
                    SocketException e("select() timed out\n");
                    throw e;
                }
            } while (1);
        } else {
            close(_sockfd);
            SocketException e("Failed to connect");
            throw e;
        }
    }
#elif _WIN32
    if (res == SOCKET_ERROR) {
        closesocket(_sockfd);
        
        SocketException e("Error connecting!");
        throw e;
    }
#endif
}

sock_msg_t ClientSocket::checkForIncomingMessages() {
    sock_msg_t msg;
    struct timeval _tv;
    
    _tv.tv_sec = 0;
    _tv.tv_usec = 50000;
    
    fd_set _readfds;
    
    FD_ZERO(&_readfds);
    FD_SET(_sockfd, &_readfds);
    int cnt = select(_sockfd+1, &_readfds, NULL, NULL, &_tv);
#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
    if (cnt == -1) {
#elif _WIN32
    if (cnt == SOCKET_ERROR) {
#endif
        SocketException e("select error!");
        _ready = false;
        throw e;
    }
    if (FD_ISSET(_sockfd, &_readfds)) {
#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
        msg.bytes = read(_sockfd, _buffer, _buffer_size);
        if(msg.bytes > 0) {
#elif _WIN32
        msg.bytes = recv(_sockfd, _buffer, _buffer_size, 0);
        if(msg.bytes > 0 && msg.bytes != SOCKET_ERROR) {
#endif
            msg.msg = new unsigned char[msg.bytes];
            memcpy(msg.msg, _buffer, msg.bytes);
        } else {
            SocketException e("Lost connection.");
            _ready = false;
            throw e;
        }
    } else {
        msg.bytes = 0;
        msg.msg = NULL;
    }
    
    return msg;
}

unsigned int ClientSocket::getBufferSize() {
    return _buffer_size;
}

void ClientSocket::send_server(sock_msg_t message) {
    if (_ready) {
        if (message.bytes < _buffer_size) {
            memcpy(_buffer, message.msg, message.bytes);
            
            unsigned long inputLength = message.bytes;
            long len;
            
            len = send(_sockfd, _buffer, message.bytes, 0);
            
            if (len < inputLength) {
                SocketException e("Failed to send message.");
                _ready = false;
                throw e;
            }
        }
    } else {
        SocketException e("Socket is closed.");
        throw e;
    }
}

bool ClientSocket::isReady() {
    return _ready;
}
