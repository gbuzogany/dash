//
//  CB650F.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "CB650F.hpp"

CB650F::CB650F() : Vehicle() {

}

float CB650F::torqueForRPM_nm(int RPM) {
    for (int i = torqueRPM.size() - 1; i >= 0; i--) {
        if (rpm >= torqueRPM[i]) {
            if (i == torqueRPM.size() - 1) {
                // if it's the last entry, just return last one, as it's not possible to interpolate
                return torque[torqueRPM.size() - 1];
            }
            else {
                // interpolate using i and i+1
                float curr_torque = torque[i];
                float next_torque = torque[i+1];
                float curr_rpm = torqueRPM[i];
                float next_rpm = torqueRPM[i+1];
                float delta = (next_torque - curr_torque) / (next_rpm - curr_rpm);
                float delta_rpm = rpm - curr_rpm;
                return curr_torque + delta * delta_rpm;
            }
        }
    }
    return 0;
}

float CB650F::currentPowerOutputForTorque_HP(float torque_nm) {
    return CB650F::rpmToRadS(rpm) * torque_nm / 1000.0f * 1.357f;
}

float CB650F::rpmToRadS(float rpm) {
    return rpm * (M_PI / 30.0f);
}

std::string CB650F::getMaxPowerString() {
    std::stringstream ss;
    float torque = torqueForRPM_nm(rpm);
    float power = currentPowerOutputForTorque_HP(torque);
    ss << std::fixed << std::setprecision(1) << power;
    return ss.str();
}

std::string CB650F::getMaxTorqueString() {
    std::stringstream ss;
    float torque = torqueForRPM_nm(rpm);
    ss << std::fixed << std::setprecision(1) << torque;
    return ss.str();
}
