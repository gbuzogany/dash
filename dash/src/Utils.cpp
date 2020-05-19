//
//  Utils.cpp
//  dash_bin
//
//  Created by Gustavo Buzogany Eboli on 19/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "Utils.hpp"

float Utils::map(float value, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}
