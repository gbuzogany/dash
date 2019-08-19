//
//  ECUConnector.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "ECUConnector.hpp"

ECUConnector::ECUConnector(std::string host,
                           unsigned int port,
                           unsigned int buffer_size,
                           int wait_timeout):
_host(host),
_port(port),
_buffer_size(buffer_size),
_wait_timeout(wait_timeout)
{
    try
    {
        _cs = std::unique_ptr<ClientSocket>(new ClientSocket(_host, _port, _buffer_size, _wait_timeout));
    }
    catch (SocketException e)
    {
        throw std::move(e);
    }
}

void ECUConnector::connect() {
    try
    {
        _cs->connectSocket();
    }
    catch (SocketException e)
    {
        throw std::move(e);
    }
}

sock_msg_t ECUConnector::poll() {
    sock_msg_t msg;
    msg.bytes = 0;
    msg.msg = NULL;
    
    try
    {
        msg = _cs->checkForIncomingMessages();
    }
    catch (SocketException e)
    {
        throw std::move(e);
    }
    return msg;
}

void ECUConnector::disconnect() {
    try
    {
        _cs.reset();
    }
    catch (SocketException e)
    {
        throw std::move(e);
    }
}

void ECUConnector::send(sock_msg_t msg) {
    _cs->send_server(msg);
    delete[] msg.msg;
}

sock_msg_t ECUConnector::requestStats() {
    sock_msg_t msg;
    sock_msg_t resp;
    resp.bytes = 0;
    
    if (_cs->isReady() == false) {
        try {
            connect();
        } catch (SocketException e) {
            // failed to connect
        }
    }
    if (_cs->isReady() == true) {
        try {
            msg.bytes = 1;
            msg.msg = (unsigned char*) malloc(1);
            msg.msg[0] = 0xCB;
            _cs->send_server(msg);
            delete[] msg.msg;
        } catch(SocketException e) {
            delete[] msg.msg;
            throw std::move(e);
        }
        while (resp.bytes == 0) {
            try {
                resp = poll();
            } catch(SocketException e) {
                throw std::move(e);
            }
            usleep(3000);
        }
    }
    return resp;
}
