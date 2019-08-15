//
//  Vehicle.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>

enum {GEAR_NONE, GEAR_N, GEAR_1, GEAR_2, GEAR_3, GEAR_4, GEAR_5, GEAR_6};

class Vehicle {
protected:
    int rpm = 0;
    int gear = GEAR_NONE;
    int neutral = 0;
    bool engineRunning = false;
    
    float speed = 0;
    float battVoltage = 12.5;
    float coolantTemp = 20.0;
    float airIntakeTemp = 20.0;
    float manifoldPressure = 0;
    float tps = 0.5;
public:
    Vehicle();
    virtual std::string getRPMString();
    virtual std::string getGearString();
    virtual std::string getSpeedString();
    virtual std::string getBattVoltageString();
    virtual std::string getCoolantTempString();
    virtual std::string getAirIntakeTempString();
    virtual std::string getManifoldPressureString();
    virtual std::string getTPSString();
    virtual std::string getMaxPowerString();
    virtual std::string getMaxTorqueString();
    virtual void* serialize() { return NULL; };
};

#endif /* Vehicle_hpp */
