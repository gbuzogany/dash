//
//  Animation.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <string>

class Animation {
    float duration, elapsed = 0, from, to;
    std::string id;
    
public:
    Animation(std::string id, float from, float to, float duration);
    float animate(float delta);
    bool complete();
    std::string getId();
};

#endif /* Animation_hpp */
