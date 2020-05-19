//
//  DashService.hpp
//  dash_bin
//
//  Created by Gustavo Buzogany Eboli on 19/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef DashService_hpp
#define DashService_hpp

#include <stdio.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "dash/proto/dash.grpc.pb.h"


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using dash::DashService;
using dash::IntValue;
using dash::FloatValue;
using dash::StringValue;
using dash::BytesValue;
using dash::StatusResponse;

class DashServiceImpl final : public DashService::Service {
public:
    DashServiceImpl();
    
    int getIntValue(std::string identifier, int& result);
    int getIntValueAsString(std::string identifier, std::string& result);
    int getFloatValue(std::string identifier, float& result);
    int getFloatValueAsString(std::string identifier, std::string& result, int precision = 0);
    int getStringValue(std::string identifier, std::string& result);
    int getBytesValue(std::string identifier, std::string& result);
    
private:
    
    std::map<std::string, int> intValues;
    std::map<std::string, float> floatValues;
    std::map<std::string, std::string> stringValues;
    std::map<std::string, std::string> byteValues;
    
    Status UpdateDashIntData(ServerContext* context, const IntValue* request, StatusResponse* response);
    Status UpdateDashFloatData(ServerContext* context, const FloatValue* request, StatusResponse* response);
    Status UpdateDashStringData(ServerContext* context, const StringValue* request, StatusResponse* response);
    Status UpdateDashBytesData(ServerContext* context, const BytesValue* request, StatusResponse* response);
};

#endif /* DashService_hpp */
