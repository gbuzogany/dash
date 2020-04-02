//
//  DashControl.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 31/03/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "DashControl.hpp"
#include "Vehicle.hpp"
#include "Dashboard.hpp"

DashControlImpl::DashControlImpl(Dashboard* dash) {
    dash_ = dash;
}

Status DashControlImpl::UpdateDashData(ServerContext* context, const DashData* request, StatusResponse* response) {
    Vehicle* vehicle = dash_->getVehicle();
    vehicle->setSpeed(request->speed());
    vehicle->setRPM(request->rpm());
    vehicle->setGear(request->gear());
    vehicle->setNeutral(request->neutral());
    vehicle->setEngineRunning(request->enginerunning());
    return Status::OK;
}

Status DashControlImpl::UpdateDashExtendedData(ServerContext *context, const DashExtendedData *request, StatusResponse *response) {
    Vehicle* vehicle = dash_->getVehicle();
    vehicle->setBatteryVoltage(request->batteryvoltage());
    vehicle->setCoolantTemperature(request->coolanttemperature());
    vehicle->setAirIntakeTemperature(request->airintaketemperature());
    vehicle->setManifoldPressure(request->manifoldpressure());
    vehicle->setThrottlePositionSensor(request->throttlepositionsensor());
    vehicle->setInjectorDuration(request->injectorduration());
    vehicle->setIgnitionAdvance(request->ignitionadvance());
    vehicle->setKickstand(request->kickstand());
    return Status::OK;
}
