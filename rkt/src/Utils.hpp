//
//  Utils.hpp
//  dash_bin
//
//  Created by Gustavo Buzogany Eboli on 19/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <sys/types.h>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum {LEFT, CENTER, RIGHT, TOP, BOTTOM};

class Utils {
    
public:
    static float map(float value, float inMin, float inMax, float outMin, float outMax);
    static std::pair<float, float> calculateTextCenter(float totalWidth, uint hAlign, uint vAlign, int fontSize);
};

#endif /* Utils_hpp */
