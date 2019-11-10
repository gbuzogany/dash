//
//  MediaServer.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 10/11/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "media.grpc.pb.h"
#include "MediaServer.hpp"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using mediaplayer::StatusResponse;
using mediaplayer::PlayStatus;
using mediaplayer::MediaItem;
using mediaplayer::MediaPlayer;

MediaServiceImpl::~MediaServiceImpl() {
    server_->Shutdown();
    // Always shutdown the completion queue after the server.
    cq_->Shutdown();
}

void MediaServiceImpl::Run() {
    std::string server_address("0.0.0.0:50051");
    
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service_" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *asynchronous* service.
    builder.RegisterService(&service_);
    // Get hold of the completion queue used for the asynchronous communication
    // with the gRPC runtime.
    cq_ = builder.AddCompletionQueue();
    // Finally assemble the server.
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    
    // Proceed to the server's main loop.
    HandleRpcs();
}

MediaServiceImpl::CallData::CallData(MediaPlayer::AsyncService* service, ServerCompletionQueue* cq)
: service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
    // Invoke the serving logic right away.
    Proceed();
}

void MediaServiceImpl::CallData::Proceed() {
    if (status_ == CREATE) {
        printf("CREATE\n");
        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;
        
        // As part of the initial CREATE state, we *request* that the system
        // start processing PlayStatusChanged requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestPlayStatusChanged(&ctx_, &playStatusRequest_, &responder_, cq_, cq_, this);
    } else if (status_ == PROCESS) {
        printf("PROCESS\n");
        // Spawn a new CallData instance to serve new clients while we process
        // the one for this CallData. The instance will deallocate itself as
        // part of its FINISH state.
        new CallData(service_, cq_);
        
        printf("%s\n", playStatusRequest_.playstatus().c_str());
        reply_.set_status(0);
        
        // And we are done! Let the gRPC runtime know we've finished, using the
        // memory address of this instance as the uniquely identifying tag for
        // the event.
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
    } else {
        printf("FINISH\n");
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
        
void MediaServiceImpl::HandleRpcs() {
    // Spawn a new CallData instance to serve new clients.
    new CallData(&service_, cq_.get());
    void* tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
        printf("loop\n");
        // Block waiting to read the next event from the completion queue. The
        // event is uniquely identified by its tag, which in this case is the
        // memory address of a CallData instance.
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or cq_ is shutting down.
        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<CallData*>(tag)->Proceed();
    }
}
