//
//  CB650F.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef CB650F_hpp
#define CB650F_hpp

#include <stdio.h>
#include <iostream>
#include <array>
#include <list>
#include "Vehicle.hpp"
#include <math.h>
#include <cmath>
#include "honda_generated.h"

enum {IN_GEAR = 0, NEUTRAL_CLUTCH = 1, KICKSTAND = 3};

class CB650F : public Vehicle
{
private:
    std::array<float, 183> torque;
    std::array<float, 183> torqueRPM;
    std::array<float, 6> gearRatios;
    
    std::array<float, 6> baseSpeed;
    std::array<float, 6> deltaSpeed;
    
    float primary_reduction = 1.690;
    float final_reduction = 2.8;
    float tire_circumference = 1.98;
    
    float torqueForRPM_nm(int RPM);
    float currentPowerOutputForTorque_HP(float torque_nm);
    static float rpmToRadS(float rpm);
public:
    CB650F();
    int guessGear();
    std::string getMaxPowerString();
    std::string getMaxTorqueString();
    void* serialize();
    void read(uint8_t *buffer_pointer);
};


#endif /* CB650F_hpp */
