//
//  SocketException.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef SocketException_h
#define SocketException_h

#include <string>

class SocketException
{
private:
    std::string msg;
    
public:
    SocketException(const std::string error_msg)
    {
        msg = error_msg;
    }
    
    std::string what()
    {
        return msg;
    }
};


#endif /* SocketException_h */
