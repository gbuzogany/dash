//
//  Vehicle.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Vehicle.hpp"

//int rpm = 0;
//int gear = GEAR_NONE;
//
//float speed = 0;
//float battVoltage = 0;
//float coolantTemp = 0;
//float airIntakeTemp = 0;
//float manifoldPressure = 0;
//float tps = 0;
//float maxPower = 0;
//float maxTorque = 0;

//std::stringstream tempSs;
//tempSs << std::fixed << std::setprecision(1) << temp;
//std::string coolantTempStr = tempSs.str();

Vehicle::Vehicle() {
    
}

std::string Vehicle::getRPMString() {
    return std::to_string(rpm);
}

std::string Vehicle::getGearString() {
    switch (gear) {
        case GEAR_NONE:
            return "-";
        case GEAR_N:
            return "N";
        case GEAR_1:
            return "1";
        case GEAR_2:
            return "2";
        case GEAR_3:
            return "3";
        case GEAR_4:
            return "4";
        case GEAR_5:
            return "5";
        case GEAR_6:
            return "6";
        default:
            return "?";
    }
}

std::string Vehicle::getSpeedString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << speed;
    return ss.str();
}

std::string Vehicle::getBattVoltageString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << battVoltage;
    return ss.str();
}

std::string Vehicle::getCoolantTempString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << coolantTemp;
    return ss.str();
}

std::string Vehicle::getAirIntakeTempString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << airIntakeTemp;
    return ss.str();
}

std::string Vehicle::getManifoldPressureString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << manifoldPressure;
    return ss.str();
}

std::string Vehicle::getTPSString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << tps;
    return ss.str();
}

std::string Vehicle::getInjectorString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << injectorDuration;
    return ss.str();
}

std::string Vehicle::getInjectorRawString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << injectorDurationRaw;
    return ss.str();
}

std::string Vehicle::getIgnitionAdvanceString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << ignitionAdvance;
    return ss.str();
}

std::string Vehicle::getO2VoltageString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << o2Voltage;
    return ss.str();
}

std::string Vehicle::getMaxPowerString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << 0;
    return ss.str();
}

std::string Vehicle::getMaxTorqueString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << 0;
    return ss.str();
}

int Vehicle::getNeutral() {
    return neutral;
}

