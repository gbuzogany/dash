//
//  Icon.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 23/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "Icon.hpp"

Icon::Icon(std::string name, int x, int y, int width, int height) : name(name), x(x), y(y), width(width), height(height) {
    
}

Icon::~Icon() {
    std::cout << "Removed icon." << std::endl;
}
