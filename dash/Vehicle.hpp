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

enum {GEAR_NONE, GEAR_1, GEAR_2, GEAR_3, GEAR_4, GEAR_5, GEAR_6, GEAR_N};

class Vehicle {
protected:
    int rpm = 0;
    int gear = GEAR_NONE;
    bool neutral = false;
    bool clutch = false;
    bool kickstand = false;
    int engineRunning = 0;
    
    float speed = 0;
    float batteryVoltage = 0;
    float coolantTemperature = 0;
    float airIntakeTemperature = 0;
    float manifoldPressure = 0;
    float throttlePositionSensor = 0;
    float injectorDuration = 0;
    float ignitionAdvance = 0;
public:
    Vehicle();
    
    void setSpeed(float speed);
    void setRPM(int rpm);
    void setGear(int gear);
    void setNeutral(bool neutral);
    void setClutch(bool clutch);
    void setKickstand(bool kickstand);
    void setEngineRunning(bool engineRunning);
    void setBatteryVoltage(float batteryVoltage);
    void setCoolantTemperature(float coolantTemperature);
    void setAirIntakeTemperature(float airIntakeTemperature);
    void setManifoldPressure(float manifoldPressure);
    void setThrottlePositionSensor(float throttlePositionSensor);
    void setInjectorDuration(float injectorDuration);
    void setIgnitionAdvance(float ignitionAdvance);
    
    bool getNeutral();
    bool getKickstand();
    bool getClutch();
    std::string getRPMString();
    std::string getGearString();
    std::string getSpeedString();
    std::string getBattVoltageString();
    std::string getCoolantTempString();
    std::string getAirIntakeTempString();
    std::string getManifoldPressureString();
    std::string getTPSString();
    std::string getInjectorString();
    std::string getIgnitionAdvanceString();
    std::string getMaxPowerString();
    std::string getMaxTorqueString();
    void read(uint8_t *buffer_pointer) {};
};

#endif /* Vehicle_hpp */
