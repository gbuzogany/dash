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
#include "Vehicle.hpp"
#include <math.h>
#include "honda_generated.h"

class CB650F : public Vehicle
{
private:
    std::array<float, 183> torque;
    std::array<float, 183> torqueRPM;
    
    float torqueForRPM_nm(int RPM);
    float currentPowerOutputForTorque_HP(float torque_nm);
    static float rpmToRadS(float rpm);
public:
    CB650F();
    std::string getMaxPowerString();
    std::string getMaxTorqueString();
    void* serialize();
    void read(uint8_t *buffer_pointer);
};


#endif /* CB650F_hpp */
