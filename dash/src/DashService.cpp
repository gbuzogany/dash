//
//  DashService.cpp
//  dash_bin
//
//  Created by Gustavo Buzogany Eboli on 19/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "DashService.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

DashServiceImpl::DashServiceImpl() {
}

int DashServiceImpl::getIntValue(std::string identifier, int& result) {
    if (intValues.find(identifier) != intValues.end()) {
        result = intValues[identifier];
        return 0;
    }
    return -1;
}

int DashServiceImpl::getIntValueAsString(std::string identifier, std::string& result) {
    if (intValues.find(identifier) != intValues.end()) {
        result = std::to_string(intValues[identifier]);
        return 0;
    }
    return -1;
}

int DashServiceImpl::getFloatValue(std::string identifier, float& result) {
    if (floatValues.find(identifier) != floatValues.end()) {
        result = floatValues[identifier];
        return 0;
    }
    return -1;
}

int DashServiceImpl::getFloatValueAsString(std::string identifier, std::string& result, int precision) {
    if (floatValues.find(identifier) != floatValues.end()) {
        float value = floatValues[identifier];
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        result = stream.str();
        return 0;
    }
    return -1;
}

int DashServiceImpl::getStringValue(std::string identifier, std::string& result) {
    if (stringValues.find(identifier) != stringValues.end()) {
        result = stringValues[identifier];
        return 0;
    }
    return -1;
}

int DashServiceImpl::getBytesValue(std::string identifier, std::string& result) {
    if (byteValues.find(identifier) != byteValues.end()) {
        result = byteValues[identifier];
        return 0;
    }
    return -1;
}

Status DashServiceImpl::UpdateDashIntData(ServerContext* context, const IntValue* request, StatusResponse* response) {
    std::string identifier = request->identifier();
    int value = request->value();
    intValues[identifier] = value;
    return Status::OK;
}

Status DashServiceImpl::UpdateDashFloatData(ServerContext* context, const FloatValue* request, StatusResponse* response) {
    std::string identifier = request->identifier();
    float value = request->value();
    floatValues[identifier] = value;
    return Status::OK;
}

Status DashServiceImpl::UpdateDashStringData(ServerContext* context, const StringValue* request, StatusResponse* response) {
    std::string identifier = request->identifier();
    std::string value = request->value();
    stringValues[identifier] = value;
    return Status::OK;
}

Status DashServiceImpl::UpdateDashBytesData(ServerContext* context, const BytesValue* request, StatusResponse* response) {
    std::string identifier = request->identifier();
    std::string value = request->value();
    byteValues[identifier] = value;
    return Status::OK;
}

