//
//  ECUConnector.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef ECUConnector_hpp
#define ECUConnector_hpp

#include <stdio.h>
#include <memory>
#include "ClientSocket.hpp"
#include "Definitions.h"

class ECUConnector
{
    std::unique_ptr<ClientSocket> _cs;
    std::string _host;
    unsigned int _port;
    unsigned int _buffer_size;
    unsigned int _encrypt;
    int _wait_timeout;
    
public:
    
    ECUConnector(std::string host,
                    unsigned int port,
                    unsigned int buffer_size,
                    int wait_timeout);
    sock_msg_t poll();
    void connect();
    void disconnect();
    sock_msg_t requestStats();
};
#endif /* ECUConnector_hpp */
