//
//  Animation.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(std::string id, float from, float to, float duration) {
    this->from = from;
    this->to = to;
    this->duration = duration;
    this->id = id;
}

float Animation::animate(float delta) {
    elapsed += delta;
    if (elapsed > duration) {
        elapsed = duration;
    }
    
    float deltaValue = to - from;
    return from + deltaValue * (elapsed / duration);
}

bool Animation::complete() {
    return elapsed < duration == false;
}

std::string Animation::getId() {
    return id;
}
