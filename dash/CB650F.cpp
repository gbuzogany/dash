//
//  CB650F.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "CB650F.hpp"

CB650F::CB650F() : Vehicle() {
    torque = {25.0, 39.0887,39.4386,39.774,40.1094,40.4374,40.7291,41.0134,41.3196,41.604,41.9758,42.282,42.5955,42.8507,43.1059,43.3902,43.6308,43.8422,44.0682,44.3526,44.615,44.9869,45.3441,45.6795,46.0149,46.3065,46.4961,46.7658,47.0575,47.1668,47.5605,48.1146,48.3479,48.6031,48.8801,49.2228,49.4415,49.7404,50.0394,50.382,50.8414,51.1403,51.4392,51.6944,51.9568,52.2193,52.3724,52.5838,52.7734,52.9119,53.0505,53.2181,53.4223,53.5098,53.6483,53.7795,53.8816,54.0055,54.0493,54.2826,54.4721,54.6982,54.8367,54.9679,55.0773,55.121,55.1794,55.1794,55.1794,55.1429,55.1356,55.1356,55.2596,55.2887,55.3689,55.4564,55.4127,55.6241,55.8282,56.0907,56.3532,56.5719,56.8416,57.1187,57.2791,57.5707,57.9936,58.2488,58.431,58.7518,58.9778,59.0945,59.2622,59.4299,59.5538,59.7288,59.8892,60.0569,60.1589,60.2464,60.3412,60.3777,60.5162,60.6401,60.7714,60.9755,61.1578,61.3109,61.515,61.6754,61.865,61.9816,62.1056,62.2076,62.2441,62.2733,62.317,62.3462,62.317,62.3389,62.3826,62.3899,62.4701,62.5139,62.5357,62.543,62.5576,62.5576,62.5357,62.4482,62.3607,62.2951,62.2368,62.1056,61.9306,61.7483,61.5515,61.3328,61.1432,60.9901,60.7932,60.5745,60.3558,60.1298,59.8673,59.6632,59.459,59.182,58.956,58.7591,58.555,58.38,58.2415,58.0373,57.7894,57.5707,57.3301,57.1041,56.7906,56.5573,56.3021,56.0397,55.7699,55.5585,55.3689,55.1575,54.9679,54.7492,54.5159,54.268,54.0201,53.7795,53.5025,53.2765,53.0942,52.8463,52.5182,52.2412,51.9641,51.7017,51.41,51.1621,50.7976};
    torqueRPM = {1000.0, 2273.15,2290.88,2308.62,2322.81,2340.55,2354.74,2368.93,2383.11,2397.3,2415.04,2429.23,2445.19,2457.61,2468.25,2493.08,2512.59,2528.56,2542.75,2562.26,2578.22,2597.73,2633.2,2665.13,2702.38,2732.53,2750.27,2773.32,2798.16,2805.25,2883.29,2940.05,2961.33,2993.26,3030.51,3069.53,3094.36,3161.76,3239.8,3317.84,3385.24,3433.13,3486.34,3537.78,3589.22,3654.84,3697.41,3736.43,3773.68,3835.76,3885.42,3938.63,4000.71,4078.75,4156.79,4234.84,4296.91,4364.31,4394.47,4447.68,4495.57,4550.55,4605.53,4658.74,4708.41,4763.39,4816.6,4887.55,4954.95,5009.93,5082.65,5181.98,5263.57,5316.78,5394.82,5483.5,5570.42,5655.55,5730.05,5799.22,5871.94,5939.34,6008.51,6091.88,6136.22,6208.94,6285.21,6345.51,6396.95,6457.25,6514.01,6545.94,6629.3,6677.19,6723.31,6794.25,6858.11,6921.96,6976.94,7047.89,7113.52,7141.89,7203.97,7266.05,7315.71,7374.25,7427.46,7482.44,7537.42,7585.31,7643.85,7691.73,7748.49,7822.99,7888.61,7959.56,8050.02,8103.23,8172.4,8268.18,8369.28,8443.77,8530.68,8621.14,8684.99,8773.68,8857.04,8951.05,9018.45,9121.32,9162.11,9211.78,9261.44,9319.97,9380.28,9437.03,9493.79,9559.42,9619.72,9662.29,9710.18,9761.62,9807.73,9860.94,9914.15,9963.82,10018.8,10086.2,10148.28,10203.26,10256.47,10304.36,10343.38,10391.27,10437.39,10483.5,10534.94,10584.6,10650.23,10692.8,10744.24,10795.67,10857.75,10910.96,10960.62,11012.06,11052.86,11091.88,11134.44,11175.24,11212.49,11253.28,11292.3,11322.45,11354.38,11389.85,11432.42,11471.44,11503.37,11538.84,11576.09,11608.02,11652.36};
    gearRatios = {3.071, 2.235, 1.777, 1.520, 1.333, 1.214};
}

float CB650F::torqueForRPM_nm(int RPM) {
    for (int i = (int) torqueRPM.size() - 1; i >= 0; i--) {
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

using namespace dash;

void* CB650F::serialize() {
    flatbuffers::FlatBufferBuilder builder(32); // current size
    
    auto message = CreateECUMessage(builder, battVoltage, coolantTemp, airIntakeTemp, manifoldPressure, speed, tps, rpm, neutral, engineRunning);
    builder.Finish(message);
    
    uint8_t *buf = builder.GetBufferPointer();
    int size = builder.GetSize();
    
    void *buffer = malloc(size);
    buffer = memcpy(buffer, buf, size);
    
    return buffer;
}

int CB650F::guessGear() {
    // neutral
    // 0 = gear 1 = neutral/clutch 3 = kickstand_neutral
    if (neutral != IN_GEAR) {
        return GEAR_NONE;
    }
    if (neutral == KICKSTAND_NEUTRAL) {
        return GEAR_N;
    }
    
    float base_wheel_speed = rpm / primary_reduction;

    for (int i = 0; i < gearRatios.size(); i++) {
        //            (            base wheel speed rpm                  ) / (sec/min) * tire_circumference * (m/s to km/h)
        baseSpeed[i] = (base_wheel_speed / gearRatios[i] / final_reduction) /   60.0f   * tire_circumference * 3.6f;
        deltaSpeed[i] = abs(speed - baseSpeed[i]);
    }
    
    int smallest_index = 0;
    float smallest_value = 9999999;
        
    for (int i = 0; i < gearRatios.size(); i++) {
        if (deltaSpeed[i] < smallest_value) {
            smallest_index = i;
            smallest_value = deltaSpeed[i];
            
        }
    }
    
    int currentGear = GEAR_NONE;
    switch (smallest_index) {
        case 0:
            currentGear = GEAR_1;
            break;
        case 1:
            currentGear = GEAR_2;
            break;
        case 2:
            currentGear = GEAR_3;
            break;
        case 3:
            currentGear = GEAR_4;
            break;
        case 4:
            currentGear = GEAR_5;
            break;
        case 5:
            currentGear = GEAR_6;
            break;
        default:
            currentGear = GEAR_NONE;
    }
    gear = currentGear;
    return currentGear;
}

void CB650F::read(uint8_t *buffer_pointer) {
    auto message  = GetECUMessage(buffer_pointer);
    
    rpm = message->rpm();
    speed = message->speed();
    battVoltage = message->battVoltage();
    coolantTemp = message->coolantTemp();
    airIntakeTemp = message->airIntakeTemp();
    manifoldPressure = message->manifoldPressure();
    neutral = message->neutral();
    engineRunning = message->engineRunning();
    tps = message->tps();
    injectorDuration = message->injDur();
    ignitionAdvance = message->ignAdv();
    o2Voltage = message->ignAdv();
    gear = guessGear();
}
