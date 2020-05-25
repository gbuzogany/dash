//
//  Icon.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 23/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef Icon_hpp
#define Icon_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Icon {
public:
    float x, y;
    float width, height;
    std::string name;
    
    Icon(std::string name, int x, int y, int width, int height);
    ~Icon();
};

#endif /* Icon_hpp */
