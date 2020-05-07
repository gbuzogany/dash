//
//  DashControl.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 31/03/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef DashControl_hpp
#define DashControl_hpp

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "dash.grpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using dash::DashControl;
using dash::DashData;
using dash::DashExtendedData;
using dash::StatusResponse;

class Dashboard;

class DashControlImpl final : public DashControl::Service {
public:
    DashControlImpl(Dashboard* dash);
private:
    Dashboard* dash_;
    
    Status UpdateDashData(ServerContext* context, const DashData* request, StatusResponse* response);
    Status UpdateDashExtendedData(ServerContext *context, const DashExtendedData *request, StatusResponse *response);
};

#endif /* DashControl_hpp */
