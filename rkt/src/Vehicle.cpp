//
//  Vehicle.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Vehicle.hpp"

Vehicle::Vehicle() {
    
}

std::string Vehicle::getRPMString() {
    return std::to_string(rpm);
}

std::string Vehicle::getGearString() {
    if (neutral == true) {
        return "N";
    }
    if (clutch == true) {
        return "-";
    }
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
    ss << std::fixed << std::setprecision(1) << batteryVoltage;
    return ss.str();
}

std::string Vehicle::getCoolantTempString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << coolantTemperature;
    return ss.str();
}

std::string Vehicle::getAirIntakeTempString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << airIntakeTemperature;
    return ss.str();
}

std::string Vehicle::getManifoldPressureString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << manifoldPressure;
    return ss.str();
}

std::string Vehicle::getTPSString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << throttlePositionSensor;
    return ss.str();
}

std::string Vehicle::getInjectorString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << injectorDuration;
    return ss.str();
}

std::string Vehicle::getIgnitionAdvanceString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << ignitionAdvance;
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

int Vehicle::getRPM() {
    return rpm;
}

bool Vehicle::getNeutral() {
    return neutral;
}

bool Vehicle::getKickstand() {
    return kickstand;
}

bool Vehicle::getClutch() {
    return kickstand;
}

void Vehicle::setSpeed(float speed) {
    this->speed = speed;
}

void Vehicle::setRPM(int rpm) {
    this->rpm = rpm;
}

void Vehicle::setGear(int gear) {
    this->gear = gear;
}

void Vehicle::setNeutral(bool neutral) {
    this->neutral = neutral;
}

void Vehicle::setClutch(bool clutch) {
    this->clutch = clutch;
}

void Vehicle::setKickstand(bool kickstand) {
    this->kickstand = kickstand;
}

void Vehicle::setEngineRunning(bool engineRunning) {
    this->engineRunning = engineRunning;
}

void Vehicle::setBatteryVoltage(float batteryVoltage) {
    this->batteryVoltage = batteryVoltage;
}

void Vehicle::setCoolantTemperature(float coolantTemperature) {
    this->coolantTemperature = coolantTemperature;
}

void Vehicle::setAirIntakeTemperature(float airIntakeTemperature) {
    this->airIntakeTemperature = airIntakeTemperature;
}

void Vehicle::setManifoldPressure(float manifoldPressure) {
    this->manifoldPressure = manifoldPressure;
}

void Vehicle::setThrottlePositionSensor(float throttlePositionSensor) {
    this->throttlePositionSensor = throttlePositionSensor;
}

void Vehicle::setInjectorDuration(float injectorDuration) {
    this->injectorDuration = injectorDuration;
}

void Vehicle::setIgnitionAdvance(float ignitionAdvance) {
    this->ignitionAdvance = ignitionAdvance;
}

